// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html

/* global Diff */

const compareViewer = [
  {
    initialDoc: '../../files/text-compare_1.pdf',
    domElement: 'leftPanel',
    diffPanel: 'compareLeftPanel',
    instance: null,
    displayingWebViewer: true,
    filenameBtn: document.querySelector('#toggleLeftBtn'),
    pageTextSections: null,
    highlightColor: '#e74c3c',
    backgroundColor: '#f9e6f0',
    textColor: '#f9e79f',
    searchTerm: '',
    searchResult: [],
    searchResultIndex: 0,
  },
  {
    initialDoc: '../../files/text-compare_2.pdf',
    domElement: 'rightPanel',
    diffPanel: 'compareRightPanel',
    instance: null,
    displayingWebViewer: false,
    pageTextSections: null,
    filenameBtn: document.querySelector('#toggleRightBtn'),
    highlightColor: '#45b39d',
    backgroundColor: '#b3f9c6',
    textColor: '#ebf5fb',
    searchTerm: '',
    searchResult: [],
    searchResultIndex: 0,
  },
];

const leftPanelIndex = 0;
const rightPanelIndex = 1;

let maxPageCount = 1;
let workerTransportPromise;
let scrollTimeout;
let pageChangeTimeout;

Core.setWorkerPath('../../../lib/core');
Core.getDefaultBackendType().then(async pdfType => {
  workerTransportPromise = Core.initPDFWorkerTransports(pdfType, {});

  await Promise.all([initializeWebViewer(compareViewer[leftPanelIndex]), initializeWebViewer(compareViewer[rightPanelIndex])]);

  maxPageCount = Math.min(compareViewer[leftPanelIndex].instance.Core.documentViewer.getPageCount(), compareViewer[rightPanelIndex].instance.Core.documentViewer.getPageCount());
  compareViewer[leftPanelIndex].instance.Core.documentViewer.setCurrentPage(1);
  compareViewer[rightPanelIndex].instance.Core.documentViewer.setCurrentPage(1);

  document.querySelector('#totalPage').textContent = maxPageCount;
  document.querySelector('#currentPage').setAttribute('max', maxPageCount);
  document.querySelector('#currentPage').value = 1;

  compareViewer[leftPanelIndex].filenameBtn.value = compareViewer[leftPanelIndex].instance.Core.documentViewer.getDocument().filename;
  compareViewer[rightPanelIndex].filenameBtn.value = compareViewer[rightPanelIndex].instance.Core.documentViewer.getDocument().filename;

  compareText(1);
});

const initializeWebViewer = viewer => {
  return new Promise(resolve => {
    WebViewer(
      {
        path: '../../../lib',
        // since there are two instance of WebViewer, use "workerTransportPromise" so viewers can share resources
        workerTransportPromise: {
          pdf: workerTransportPromise,
        },
        initialDoc: viewer.initialDoc,
        disabledElements: ['toggleNotesButton', 'pageNavOverlay', 'searchButton'],
      },
      document.getElementById(`${viewer.domElement}`)
    ).then(instance => {
      const { documentViewer } = instance.Core;
      const Core = instance.Core;
      const { Feature, FitMode } = instance.UI;
      viewer.instance = instance;
      // disable tools and editing annotations
      instance.UI.disableTools();
      instance.UI.disableFeatures(Feature.Annotations);

      documentViewer.addEventListener('documentLoaded', async () => {
        const displayModeManager = documentViewer.getDisplayModeManager();
        const displayMode = displayModeManager.isVirtualDisplayEnabled()
          ? new Core.VirtualDisplayMode(documentViewer, Core.DisplayModes.Single)
          : new Core.DisplayMode(documentViewer, Core.DisplayModes.Single);
        displayModeManager.setDisplayMode(displayMode);
        instance.UI.setFitMode(FitMode.FitWidth);
        resolve(instance);
      });

      documentViewer.addEventListener('pageNumberUpdated', pageNumber => {
        if (pageNumber > maxPageCount) {
          documentViewer.setCurrentPage(maxPageCount);
          return;
        }

        document.querySelector('#currentPage').value = pageNumber;
        // update compare when page change, use debouncing to limit the amount of processing being done
        clearTimeout(pageChangeTimeout);
        pageChangeTimeout = setTimeout(() => {
          const otherViewer = compareViewer[leftPanelIndex].instance === instance ? compareViewer[rightPanelIndex].instance : compareViewer[leftPanelIndex].instance;
          if (otherViewer.Core.documentViewer.getCurrentPage() !== pageNumber) {
            otherViewer.Core.documentViewer.setCurrentPage(pageNumber);
          }
          compareText(pageNumber);
        }, 1000);
      });

      const documentContainer = document
        .getElementById(`${viewer.domElement}`)
        .querySelector('iframe')
        .contentDocument.querySelector('.DocumentContainer');
      documentContainer.onscroll = () => {
        syncScrolls(documentContainer.scrollLeft, documentContainer.scrollTop);
        clearTimeout(scrollTimeout);
      };

      documentViewer.addEventListener('zoomUpdated', zoom => {
        syncZoom(zoom, viewer.domElement);
      });
    });
  });
};

const getPageText = (instance, pageNumber) => {
  const doc = instance.Core.documentViewer.getDocument();

  return new Promise(resolve => {
    doc.loadPageText(pageNumber, text => {
      resolve(text);
    });
  });
};

const compareText = async pageNumber => {
  const text0 = await getPageText(compareViewer[leftPanelIndex].instance, pageNumber);
  const text1 = await getPageText(compareViewer[rightPanelIndex].instance, pageNumber);

  compareViewer[leftPanelIndex].pageTextSections = [];
  compareViewer[rightPanelIndex].pageTextSections = [];

  const leftPanel = document.querySelector(`#${compareViewer[leftPanelIndex].diffPanel}`);
  const rightPanel = document.querySelector(`#${compareViewer[rightPanelIndex].diffPanel}`);
  leftPanel.innerHTML = '';
  rightPanel.innerHTML = '';

  let sectionIndex = 0;

  const diffLines = Diff.diffLines(text0, text1);
  for (let i = 0; i < diffLines.length; i++) {
    const diffLine = diffLines[i];
    const sectionLeft = document.createElement('div');
    const sectionRight = document.createElement('div');
    sectionLeft.className = 'section';
    sectionRight.className = 'section';

    if (!diffLine.removed && !diffLine.added) {
      // handle case when the text are the same
      // add a toggleable element that displayed the same text when double clicked

      compareViewer[leftPanelIndex].pageTextSections.push(diffLine.value);
      compareViewer[rightPanelIndex].pageTextSections.push(diffLine.value);
      sectionLeft.setAttribute('section', sectionIndex);
      sectionRight.setAttribute('section', sectionIndex);

      sectionLeft.className = 'section identical';
      sectionRight.className = 'section identical';

      const btnLeft = document.createElement('span');
      const btnRight = document.createElement('span');
      btnLeft.innerHTML = '(...)';
      btnRight.innerHTML = '(...)';

      const textRight = document.createElement('p');
      const textLeft = document.createElement('p');
      textRight.innerHTML = diffLine.value.replace(/\r?\n/g, '<br />');
      textRight.className = 'hidden';

      textLeft.innerHTML = diffLine.value.replace(/\r?\n/g, '<br />');
      textLeft.className = 'hidden';

      sectionRight.appendChild(textRight);
      sectionLeft.appendChild(textLeft);

      sectionLeft.appendChild(btnLeft);
      sectionRight.appendChild(btnRight);

      const toggleText = () => {
        if (window.getSelection().toString()) {
          // return if highlighting text
          return;
        }
        const displayingText = !(textLeft.className !== 'hidden');

        textLeft.className = displayingText ? '' : 'hidden';
        textRight.className = displayingText ? '' : 'hidden';
        btnRight.className = displayingText ? 'hidden' : '';
        btnLeft.className = displayingText ? 'hidden' : '';
      };

      sectionRight.addEventListener('mouseup', toggleText);
      sectionLeft.addEventListener('mouseup', toggleText);

      leftPanel.appendChild(sectionLeft);
      rightPanel.appendChild(sectionRight);
    } else {
      let updatedLine = '';

      if (i + 1 < diffLines.length && (diffLines[i + 1].removed || diffLines[i + 1].added)) {
        updatedLine = diffLines[i + 1].value;
        sectionLeft.setAttribute('section', sectionIndex);
        sectionRight.setAttribute('section', sectionIndex);
        compareViewer[leftPanelIndex].pageTextSections.push(diffLines[i].value);
        compareViewer[rightPanelIndex].pageTextSections.push(diffLines[i + 1].value);
        i++;
      }

      // get difference for individual characters so they can be highlighted
      const diffChars = Diff.diffChars(diffLine.value, updatedLine);
      let oldText = '';
      let newText = '';

      const addStyle = `background-color: ${compareViewer[rightPanelIndex].highlightColor}; color: ${compareViewer[rightPanelIndex].textColor};`;
      const removeStyle = `background-color:${compareViewer[leftPanelIndex].highlightColor}; color: ${compareViewer[leftPanelIndex].textColor};`;
      diffChars.forEach(char => {
        const value = char.value.replace(/\r?\n/g, '&nbsp;<br />');

        if (!char.removed && !char.added) {
          oldText += `<span>${value}</span>`;
          newText += `<span>${value}</span>`;
        } else if (char.added) {
          newText += value.replace(/\s/g, '').length ? `<span style="${addStyle}">${value}</span>` : value;
        } else if (char.removed) {
          oldText += value.replace(/\s/g, '').length ? `<span style="${removeStyle}">${value}</span>` : value;
        }
      });

      sectionRight.style.backgroundColor = compareViewer[rightPanelIndex].backgroundColor;
      sectionLeft.style.backgroundColor = compareViewer[leftPanelIndex].backgroundColor;

      const textLeft = document.createElement('p');
      textLeft.innerHTML = oldText;
      sectionLeft.appendChild(textLeft);
      leftPanel.appendChild(sectionLeft);

      const textRight = document.createElement('p');
      textRight.innerHTML = newText;
      sectionRight.appendChild(textRight);
      rightPanel.appendChild(sectionRight);

      const maxHeight = Math.max(sectionRight.scrollHeight, sectionLeft.scrollHeight);
      sectionRight.style.height = `${maxHeight}px`;
      sectionLeft.style.height = `${maxHeight}px`;
    }

    sectionIndex++;
  }
};

const syncZoom = (zoom, domElement) => {
  compareViewer.forEach(viewer => {
    const instance = viewer.instance;

    if (instance.UI.getZoomLevel() !== zoom && domElement !== viewer.domElement) {
      instance.UI.setZoomLevel(zoom);
    }
  });
};

const syncScrolls = (scrollLeft, scrollTop) => {
  compareViewer.forEach(viewer => {
    const documentContainer = document
      .getElementById(`${viewer.domElement}`)
      .querySelector('iframe')
      .contentDocument.querySelector('.DocumentContainer');
    if (!documentContainer) {
      return;
    }

    if (documentContainer.scrollLeft !== scrollLeft) {
      documentContainer.scrollLeft = scrollLeft;
    }

    if (documentContainer.scrollTop !== scrollTop) {
      documentContainer.scrollTop = scrollTop;
    }
  });
};

let scrollDebounce = 0;
const scrollDebounceTime = 10;

// re render the top display when window resize
window.onresize = () => {
  if (compareViewer[leftPanelIndex].instance && compareViewer[leftPanelIndex].instance.Core.documentViewer) {
    compareText(compareViewer[leftPanelIndex].instance.Core.documentViewer.getCurrentPage());
  }
};

document.querySelector('#currentPage').onchange = e => {
  const value = e.currentTarget.value;
  if (value <= maxPageCount) {
    compareViewer[leftPanelIndex].instance.Core.documentViewer.setCurrentPage(value);
    compareViewer[rightPanelIndex].instance.Core.documentViewer.setCurrentPage(value);
  }
};

// sync the top displays
document.getElementById('compareLeftPanel').onscroll = e => {
  clearTimeout(scrollDebounce);

  scrollDebounce = setTimeout(() => {
    document.getElementById('compareRightPanel').scrollTop = e.target.scrollTop;
  }, scrollDebounceTime);
};

document.getElementById('compareRightPanel').onscroll = e => {
  clearTimeout(scrollDebounce);

  scrollDebounce = setTimeout(() => {
    document.getElementById('compareLeftPanel').scrollTop = e.target.scrollTop;
  }, scrollDebounceTime);
};

const toggleWebViewer = () => {
  if (compareViewer[leftPanelIndex].displayingWebViewer) {
    document.getElementById('toggleRightBtn').disabled = true;
    document.getElementById('toggleLeftBtn').disabled = false;

    document.getElementById('rightPanel').classList.remove('hidden');
    document.getElementById('leftPanel').classList.add('hidden');

    compareViewer[leftPanelIndex].displayingWebViewer = false;
    compareViewer[rightPanelIndex].displayingWebViewer = true;
  } else {
    document.getElementById('toggleRightBtn').disabled = false;
    document.getElementById('toggleLeftBtn').disabled = true;

    document.getElementById('rightPanel').classList.add('hidden');
    document.getElementById('leftPanel').classList.remove('hidden');

    compareViewer[leftPanelIndex].displayingWebViewer = true;
    compareViewer[rightPanelIndex].displayingWebViewer = false;
  }
};

document.getElementById('expandTextBtn').onclick = () => {
  document.getElementById('expandTextBtn').hidden = true;
  document.getElementById('shirkTextBtn').hidden = false;

  Array.from(document.querySelectorAll('#compareLeftPanel>.identical')).forEach(identicalSection => {
    identicalSection.querySelector('p').classList.remove('hidden');
    identicalSection.querySelector('span').classList.add('hidden');
  });

  Array.from(document.querySelectorAll('#compareRightPanel>.identical')).forEach(identicalSection => {
    identicalSection.querySelector('p').classList.remove('hidden');
    identicalSection.querySelector('span').classList.add('hidden');
  });
};

document.getElementById('shirkTextBtn').onclick = () => {
  document.getElementById('expandTextBtn').hidden = false;
  document.getElementById('shirkTextBtn').hidden = true;

  Array.from(document.querySelectorAll('#compareLeftPanel>.identical')).forEach(identicalSection => {
    identicalSection.querySelector('p').classList.add('hidden');
    identicalSection.querySelector('span').classList.remove('hidden');
  });

  Array.from(document.querySelectorAll('#compareRightPanel>.identical')).forEach(identicalSection => {
    identicalSection.querySelector('p').classList.add('hidden');
    identicalSection.querySelector('span').classList.remove('hidden');
  });
};

document.getElementById('colorPopup').onclick = e => {
  e.stopPropagation();
  const popup = document.querySelector('#colorFormPopup');
  popup.hidden = !popup.hidden;
};

document.getElementById('colorFormPopup').onclick = e => {
  e.stopPropagation();
};

document.getElementById('compareContainer').onclick = () => {
  document.querySelector('#colorFormPopup').hidden = true;
};

const colorInputs = [
  {
    element: document.getElementById('rightHighlightColor'),
    viewer: compareViewer[0],
    color: 'highlightColor',
  },
  {
    element: document.getElementById('rightBackgroundColor'),
    viewer: compareViewer[0],
    color: 'backgroundColor',
  },
  {
    element: document.getElementById('rightTextColor'),
    viewer: compareViewer[0],
    color: 'textColor',
  },
  {
    element: document.getElementById('leftHighlightColor'),
    viewer: compareViewer[1],
    color: 'highlightColor',
  },
  {
    element: document.getElementById('leftBackgroundColor'),
    viewer: compareViewer[1],
    color: 'backgroundColor',
  },
  {
    element: document.getElementById('leftTextColor'),
    viewer: compareViewer[1],
    color: 'textColor',
  },
];

colorInputs.forEach(colorInput => {
  colorInput.element.onchange = e => {
    colorInput.viewer[colorInput.color] = e.srcElement.value;
    compareText(compareViewer[0].instance.Core.documentViewer.getCurrentPage());
  };
});

document.getElementById('toggleLeftBtn').onclick = () => {
  toggleWebViewer();
};

document.getElementById('toggleRightBtn').onclick = () => {
  toggleWebViewer();
};

const loadDocuments = (leftDocument, rightDocument) => {
  let leftLoadDocumentPromise = Promise.resolve();
  let rightLoadDocumentPromise = Promise.resolve();

  if (leftDocument) {
    document.querySelector(`#${compareViewer[leftPanelIndex].diffPanel}`).innerHTML = '';
    leftLoadDocumentPromise = new Promise(resolve => {
      compareViewer[leftPanelIndex].instance.Core.documentViewer.addEventListener(
        'documentLoaded',
        () => {
          resolve();
        },
        { once: true }
      );
    });
    compareViewer[leftPanelIndex].instance.UI.loadDocument(leftDocument);
  }

  if (rightDocument) {
    document.querySelector(`#${compareViewer[rightPanelIndex].diffPanel}`).innerHTML = '';
    rightLoadDocumentPromise = new Promise(resolve => {
      compareViewer[rightPanelIndex].instance.Core.documentViewer.addEventListener(
        'documentLoaded',
        () => {
          resolve();
        },
        { once: true }
      );
    });
    compareViewer[rightPanelIndex].instance.UI.loadDocument(rightDocument);
  }

  Promise.all([leftLoadDocumentPromise, rightLoadDocumentPromise]).then(() => {
    // wait for both documents to finish loading before getting file information and comparing them
    maxPageCount = Math.min(compareViewer[leftPanelIndex].instance.Core.documentViewer.getPageCount(), compareViewer[rightPanelIndex].instance.Core.documentViewer.getPageCount());
    compareViewer[leftPanelIndex].instance.Core.documentViewer.setCurrentPage(1);
    compareViewer[rightPanelIndex].instance.Core.documentViewer.setCurrentPage(1);

    document.querySelector('#totalPage').textContent = maxPageCount;
    document.querySelector('#currentPage').setAttribute('max', maxPageCount);
    document.querySelector('#currentPage').value = 1;

    compareViewer[leftPanelIndex].filenameBtn.value = compareViewer[leftPanelIndex].instance.Core.documentViewer.getDocument().filename;
    compareViewer[rightPanelIndex].filenameBtn.value = compareViewer[rightPanelIndex].instance.Core.documentViewer.getDocument().filename;

    compareText(1);
  });
};

document.getElementById('dropdown-form').onsubmit = e => {
  e.preventDefault();
  loadDocuments(document.querySelector('#leftPanel-select').value, document.querySelector('#rightPanel-select').value);
};

document.getElementById('url-form').onsubmit = e => {
  e.preventDefault();
  loadDocuments(document.querySelector('#leftPanel-url').value, document.querySelector('#rightPanel-url').value);
};

document.getElementById('file-picker-form').onsubmit = e => {
  e.preventDefault();
  loadDocuments(document.querySelector('#leftPanel-file-picker').files[0], document.querySelector('#rightPanel-file-picker').files[0]);
};

document.getElementById('findSelectedBtn').onclick = () => {
  // get the currently selected text. We need to replace new lines with spaces for matching later.
  const selection = window.getSelection();
  // in "compareText", it set new lines to be "&nbsp;<br />", this undo it if needed
  const selectedText = selection.toString().replace(/\s*\n/gm, ' ');
  if (!selectedText) {
    alert('No text selected to find');
    return;
  }

  const selectedTextSection = selection.baseNode.parentElement.closest('.section');
  const selectionNumber = parseInt(selectedTextSection.getAttribute('section'), 10);

  let currentViewer = null;

  if (selection.baseNode.parentElement.closest('.viewer').id === 'compareRightPanel') {
    currentViewer = compareViewer[rightPanelIndex];
  } else {
    currentViewer = compareViewer[leftPanelIndex];
  }

  if (!currentViewer.displayingWebViewer) {
    // if we aren't displaying the current viewer toggle to show it
    toggleWebViewer();
  }

  // since we are searching all the text on a page, we need to find the number of previous occurrences of the search term
  const sectionElements = Array.from(selection.baseNode.parentNode.parentElement.children);
  let currentPreviousText = '';

  for (let i = 0; sectionElements.length > i; i++) {
    if (sectionElements[i] === selection.baseNode.parentElement) {
      currentPreviousText += sectionElements[i].textContent.substring(0, selection.anchorOffset);
      break;
    }
    currentPreviousText += sectionElements[i].textContent;
  }

  const previousSectionText = currentViewer.pageTextSections
    .filter((t, i) => i < selectionNumber)
    .map(t => t.replace(/\s*\n/gm, ' '))
    .join(' ');
  const previousText = `${previousSectionText}${currentPreviousText}`;

  const matches = previousText.match(new RegExp(`${selectedText.replace(/[-[\]{}()*+?.,\\^$|#]/g, '\\$&').trim()}`, 'g'));
  const previousOccurrencesInSection = matches ? matches.length : 0;

  let count = 0;
  const mode =
    currentViewer.instance.Core.documentViewer.SearchMode.e_highlight |
    currentViewer.instance.Core.documentViewer.SearchMode.e_ambient_string |
    currentViewer.instance.Core.documentViewer.SearchMode.e_case_sensitive;
  const searchOptions = {
    onResult: result => {
      if (count === previousOccurrencesInSection) {
        // skip all the previous occurrences of the search term till we get to the currently selected text
        currentViewer.instance.Core.documentViewer.displaySearchResult(result);
      }
      count++;
    },
    fullSearch: true,
    startPage: currentViewer.instance.Core.documentViewer.getCurrentPage(),
    endPage: currentViewer.instance.Core.documentViewer.getCurrentPage(),
  };

  currentViewer.instance.Core.documentViewer.textSearchInit(selectedText.trim(), mode, searchOptions);
};

document.getElementById('searchForm').onsubmit = e => {
  e.preventDefault();
  const currentSearchTerm = document.getElementById('textSearch').value;
  const viewer = compareViewer[leftPanelIndex].displayingWebViewer ? compareViewer[leftPanelIndex] : compareViewer[rightPanelIndex];

  if (viewer.searchTerm === currentSearchTerm && viewer.searchResult.length) {
    // cycle through existing results
    viewer.searchResultIndex = viewer.searchResultIndex + 1 < viewer.searchResult.length ? viewer.searchResultIndex + 1 : 0;
    viewer.instance.Core.documentViewer.displaySearchResult(viewer.searchResult[viewer.searchResultIndex]);
  } else {
    viewer.searchTerm = currentSearchTerm;
    viewer.searchResult = [];

    const mode =
      viewer.instance.Core.documentViewer.SearchMode.e_highlight | viewer.instance.Core.documentViewer.SearchMode.e_ambient_string | viewer.instance.Core.documentViewer.SearchMode.e_case_sensitive;
    const isFullSearch = true;
    viewer.instance.Core.documentViewer.textSearchInit(currentSearchTerm, mode, isFullSearch, result => {
      // this callback get called as search term are found till the final "Done" result is returned

      if (result.resultCode === Core.Search.ResultCode.FOUND) {
        if (viewer.searchResult.length === 0) {
          // display the first result received
          viewer.instance.Core.documentViewer.displaySearchResult(result);
        }
        // store results for cycling through search, check "resultCode" to not add the "done" result
        viewer.searchResult.push(result);
      } else if (result.resultCode === Core.Search.ResultCode.DONE && !viewer.searchResult.length) {
        alert(`No results found for ${currentSearchTerm}`);
      }
    });
  }
};
