(function(exports) {
  const MIDDLE_PANEL = 'resultPanel';
  const TRANSFORMATION_TYPE = {
    // some arbitrary unique values
    HORIZONTAL_TRANSLATION_INC: 'HORIZONTAL_TRANSLATION_INC',
    HORIZONTAL_TRANSLATION_DEC: 'HORIZONTAL_TRANSLATION_DEC',
    VERTICAL_TRANSLATION_INC: 'VERTICAL_TRANSLATION_INC',
    VERTICAL_TRANSLATION_DEC: 'VERTICAL_TRANSLATION_DEC',
    ROTATION_INC: 'ROTATION_INC',
    ROTATION_DEC: 'ROTATION_DEC',
    SCALE_IN: 'SCALE_IN',
    SCALE_OUT: 'SCALE_OUT',
  };
  let mouseDownIntervalId;
  let callbackFunction;

  function renderSVGIcons(nudgeDiffToolElement) {
    const url = window.location.href;
    const elementIdToSVGMapping = {
      rotateCounterClockwise: 'rotate_left.svg',
      rotateClockwise: 'rotate_right.svg',
      translateUp: 'arrow_up.svg',
      translateLeft: 'arrow_left.svg',
      translateRight: 'arrow_right.svg',
      translateDown: 'arrow_down.svg',
      scaleOut: 'size_decrease.svg',
      scaleIn: 'size_increase.svg',
    };
    Object.keys(elementIdToSVGMapping).forEach(elementId => {
      const nudgeButtonElement = nudgeDiffToolElement.getElementsByClassName(elementId)[0];
      const img = document.createElement('img');
      img.draggable = false;
      img.setAttribute('src', `${url}/assets/${elementIdToSVGMapping[elementId]}`);
      if (nudgeButtonElement) {
        nudgeButtonElement.appendChild(img);
      }
    });
  }

  function detectMouseLeftButton(evt) {
    evt = evt || window.event;
    if ('buttons' in evt) {
      return evt.buttons === 1;
    }
    const button = evt.which || evt.button;
    return button === 1;
  }

  function setUpEventListenersForTool(nudgeDiffToolElement) {
    const elementIdToOperationMapping = {
      rotateCounterClockwise: TRANSFORMATION_TYPE.ROTATION_DEC,
      rotateClockwise: TRANSFORMATION_TYPE.ROTATION_INC,
      translateUp: TRANSFORMATION_TYPE.VERTICAL_TRANSLATION_DEC,
      translateLeft: TRANSFORMATION_TYPE.HORIZONTAL_TRANSLATION_DEC,
      translateRight: TRANSFORMATION_TYPE.HORIZONTAL_TRANSLATION_INC,
      translateDown: TRANSFORMATION_TYPE.VERTICAL_TRANSLATION_INC,
      scaleOut: TRANSFORMATION_TYPE.SCALE_OUT,
      scaleIn: TRANSFORMATION_TYPE.SCALE_IN,
    };
    function activateFxn(elementId) {
      const operationType = elementIdToOperationMapping[elementId];
      if (callbackFunction) {
        callbackFunction(operationType);
      }
      mouseDownIntervalId = setInterval(() => {
        if (callbackFunction) {
          callbackFunction(operationType);
        }
      }, 250);
    }
    function deactivateFxn() {
      clearInterval(mouseDownIntervalId);
    }
    Object.keys(elementIdToOperationMapping).forEach(elementId => {
      const element = nudgeDiffToolElement.getElementsByClassName(elementId)[0];
      element.onmousedown = activateFxn.bind(this, elementId);
      element.onmouseup = deactivateFxn;
      element.onmouseenter = e => {
        if (detectMouseLeftButton(e)) {
          activateFxn(elementId);
        }
      };
      element.onmouseleave = e => {
        if (detectMouseLeftButton(e)) {
          deactivateFxn();
        }
      };
      element.ontouchstart = e => {
        e.preventDefault();
        activateFxn(elementId);
      };
      element.ontouchend = deactivateFxn;
    });
  }

  function initializeNudgeTool(callbackFunctionParam) {
    callbackFunction = callbackFunctionParam;
    const nudgeDiffToolElement = document.createElement('div');
    nudgeDiffToolElement.setAttribute('id', 'nudge-diff-tool');
    nudgeDiffToolElement.innerHTML = `
       <div class="action-group">
        <div class="action rotateCounterClockwise"></div>
        <div class="action rotateClockwise"></div>
       </div>
       <div>
        <div class="action translateUp"></div>
       <div class="action-group">
        <div class="action translateLeft"></div>
         <div class="action translateRight"></div>
       </div>
       <div class="action translateDown"></div>
       </div>
      <div class="action-group">
      <div class="action scaleOut"></div>
      <div class="action scaleIn"></div>
      </div>`;
    renderSVGIcons(nudgeDiffToolElement);
    setUpEventListenersForTool(nudgeDiffToolElement);

    const viewerElementBody = document
      .getElementById(MIDDLE_PANEL)
      .querySelector('iframe')
      .contentDocument.querySelector('body');
    viewerElementBody.insertBefore(nudgeDiffToolElement, viewerElementBody.firstChild);
  }

  exports.NudgeTool = {
    initializeNudgeTool,
    TRANSFORMATION_TYPE,
  };
})(window);
