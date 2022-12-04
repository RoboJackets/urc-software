$(() => {
  const $document = $(document); // noneed

  let pageCount = 0;
  const status = {
    NOT_STARTED: 0,
    QUEUED: 1,
    STARTED: 2,
    FINISHED: 3,
  };
  // used to keep track of whether we have loaded the page or not
  const pageStatus = [];
  // used to keep track of what order to render each page in
  const renderQueue = [];

  const isUndefined = function(val) {
    return typeof val === 'undefined';
  };

  // use instead of window.location.hash because of https://bugzilla.mozilla.org/show_bug.cgi?id=483304
  const getWindowHash = function() {
    const url = window.location.href;
    const i = url.indexOf('#');
    return i >= 0 ? url.substring(i + 1) : '';
  };

  const getQueryStringMap = function(useHash) {
    if (isUndefined(useHash)) {
      useHash = true;
    }
    const varMap = {};
    // if useHash is false then we'll use the parameters after '?'
    const queryString = useHash ? getWindowHash() : window.location.search.substring(1);
    const fieldValPairs = queryString.split('&');

    for (let i = 0; i < fieldValPairs.length; i++) {
      const fieldVal = fieldValPairs[i].split('=');
      varMap[fieldVal[0]] = fieldVal[1];
    }

    return {
      getBoolean: function(field, defaultValue) {
        let value = varMap[field];

        if (!isUndefined(value)) {
          value = value.toLowerCase();

          if (value === 'true' || value === 'yes' || value === '1') {
            return true;
          }
          if (value === 'false' || value === 'no' || value === '0') {
            return false;
          }
          // convert to boolean
          return !!field;
        }
        if (isUndefined(defaultValue)) {
          return null;
        }
        return defaultValue;
      },

      getString: function(field, defaultValue) {
        const value = varMap[field];

        if (!isUndefined(value)) {
          return decodeURIComponent(value);
        }
        if (isUndefined(defaultValue)) {
          return null;
        }
        return defaultValue;
      },
    };
  };

  const queryParams = getQueryStringMap();

  // get the document location from the query string (eg ?d=/files/myfile.xod)
  const docLocation = queryParams.getString('d');

  if (docLocation === null) {
    return;
  }

  let renderData;
  window.loadDocument(docLocation).then(renderInfo => {
    renderData = renderInfo;
    $document.trigger('documentLoaded');
  });

  function addSlide(pageIndex) {
    const slide = $('<section>')
      .attr('id', 'page' + pageIndex)
      .addClass('slide');
    slide.append($('<div class="loading">'));
    $('body').append(slide);
  }

  function loadCanvas(pageIndex) {
    if (pageIndex < 0 || pageIndex >= pageCount) {
      return;
    }

    const renderNextPage = () => {
      const pageIndex = renderQueue[0];
      pageStatus[pageIndex] = status.STARTED;

      window.loadCanvasAsync(renderData, pageIndex + 1).then(canvas => {
        pageStatus[pageIndex] = status.FINISHED;
        const $canvas = $(canvas);
        $canvas.addClass('canvasPage');

        const pageContainer = $('#page' + pageIndex); // obj that contains slides
        pageContainer.append($canvas);
        pageContainer.find('.loading').remove();

        // trigger page rescale
        $.deck('enableScale'); // mayneed

        // make sure page is centered for very large page sizes by using a negative margin
        const widthDiff = parseFloat($canvas.css('width')) - pageContainer.find('.deck-slide-scaler').width();
        // console.log("widthDiff = " + widthDiff);
        // if (widthDiff > 0) {
        $canvas.css('margin-left', -widthDiff / 2 + 'px');
        // }
        if (renderQueue.length > 1) {
          setTimeout(() => {
            renderQueue.shift();
            renderNextPage();
          }, 0);
        } else {
          renderQueue.shift();
        }
      });
    };

    if (pageStatus[pageIndex] === status.NOT_STARTED) {
      renderQueue.push(pageIndex);
      pageStatus[pageIndex] = status.QUEUED;
      if (renderQueue.length === 1) {
        renderNextPage();
      }
    }
  }

  $document.on('documentLoaded', () => {
    pageCount = renderData.pagecount;
    for (let i = 0; i < pageCount; i++) {
      addSlide(i);
      pageStatus.push(status.NOT_STARTED);
    }

    // initially load the first three pages
    for (let j = 0; j < Math.min(pageCount, 10); j++) {
      loadCanvas(j);
    }

    // initialize the deck
    $.deck('.slide');
  });

  $document.on('deck.change', (event, from, to) => {
    // load the previous, current and next pages on a page change
    // note that if they are already loaded they won't be loaded again
    loadCanvas(to - 1);
    loadCanvas(to);
    loadCanvas(to + 1);
  });
});
// # sourceURL=viewer.js
