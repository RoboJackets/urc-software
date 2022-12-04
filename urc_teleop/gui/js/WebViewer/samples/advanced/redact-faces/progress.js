const template = `
<div class="redact-progress">
  <div class="white-out"></div>
  <div class="redact-progress-content"></div>
</div>
`;

/**
 * Create Dom elements that are used for displaying face detection progress
 */
function addProgressContainerToDom() {
  const viewerDomElement = document.querySelector('#viewer');
  const existingProgressContainer = viewerDomElement.querySelector('#redact-progress-container');
  if (existingProgressContainer) {
    viewerDomElement.removeChild(existingProgressContainer);
  }
  const redactProgressContainerDiv = document.createElement('div');
  redactProgressContainerDiv.setAttribute('id', 'redact-progress-container');
  redactProgressContainerDiv.classList.add('hidden');
  redactProgressContainerDiv.innerHTML = template;
  viewerDomElement.insertBefore(redactProgressContainerDiv, viewerDomElement.firstChild);
}

/**
 * Creates custom HTML component that shows progress of face detection
 *
 * @param {number} totalNumberOfPages Total number of pages in the document
 * @returns {{showProgress: function, hideProgress: function, sendPageProcessing: function}} Object containing functions that control progress
 */
// eslint-disable-next-line no-unused-vars
function createProgress(totalNumberOfPages) {
  let processedSoFar = 0;
  const pageProcessedEventType = 'page-processed';
  addProgressContainerToDom();
  const progressContainer = document.querySelector('#redact-progress-container');
  const progressContent = document.querySelector('.redact-progress-content');

  // creating custom event listener for listening page processed events
  progressContent.addEventListener(pageProcessedEventType, () => {
    processedSoFar++;
    progressContent.innerHTML = `Detecting faces from page ${processedSoFar} / ${totalNumberOfPages}`;
  });

  function sendPageProcessing() {
    const pageProcessedEvent = new CustomEvent(pageProcessedEventType);
    progressContent.dispatchEvent(pageProcessedEvent);
  }

  function showProgress() {
    progressContainer.classList.remove('hidden');
    progressContainer.classList.add('visible');
  }
  function hideProgress() {
    progressContainer.classList.remove('visible');
    progressContainer.classList.add('hidden');
  }
  return {
    showProgress,
    hideProgress,
    sendPageProcessing,
  };
}
