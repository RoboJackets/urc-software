/* global faceapi, createProgress */
/**
 * Converts given Canvas to HTMLImageElement.
 *
 * @param {Canvas} canvas Canvas from which Image is created
 * @returns {Promise} Resolving to HTMLImageElement
 */
function convertCanvasToImage(canvas) {
  return new Promise(resolve => {
    const base64ImageDataURL = canvas.toDataURL('image/jpeg');
    const image = new Image();
    image.onload = () => {
      // resolve image once it is fully loaded
      resolve(image);
    };
    image.src = base64ImageDataURL;
  });
}

/**
 * Creates RedactionAnnotation and adds them to document.
 *
 * Note: This doesn't apply faceDetections, if you want to apply faceDetections
 * programmatically see AnnotationManager.applyRedaction()
 *
 * @param {WebViewerInstance} webViewerInstance current instance on WebViewer
 * @param {Number} pageNumber Page number of the document where detections were found
 * @param {FaceDetection[]} faceDetections Faces that were detected by face-api.js
 */
function createFaceRedactionAnnotation(webViewerInstance, pageNumber, faceDetections) {
  if (faceDetections && faceDetections.length > 0) {
    const { Annotations, annotationManager, Math } = webViewerInstance.Core;
    // We create a quad per detected face to allow us use only one redaction annotation.
    // You could create new RedactionAnnotation for each detected face, but in case where document contains
    // tens or hundreds of face applying reduction comes slow.
    const quads = faceDetections.map(detection => {
      const x = detection.box.x;
      const y = detection.box.y;
      const width = detection.box.width;
      const height = detection.box.height;

      const topLeft = [x, y];
      const topRight = [x + width, y];
      const bottomLeft = [x, y + height];
      const bottomRight = [x + width, y + height];
      // Quad is defined as points going from bottom left -> bottom right -> top right -> top left
      return new Math.Quad(...bottomLeft, ...bottomRight, ...topRight, ...topLeft);
    });
    const faceAnnotation = new Annotations.RedactionAnnotation({
      Quads: quads,
    });
    faceAnnotation.Author = annotationManager.getCurrentUser();
    faceAnnotation.PageNumber = pageNumber;
    faceAnnotation.StrokeColor = new Annotations.Color(255, 0, 0, 1);
    annotationManager.addAnnotation(faceAnnotation, false);
    // Annotation needs to be redrawn so that it becomes visible immediately rather than on next time page is refreshed
    annotationManager.redrawAnnotation(faceAnnotation);
  }
}

/**
 *
 * @param {WebViewerInstance} webViewerInstance current instance on WebViewer
 * @param {Number} pageNumber Page number of the document where detection is ran
 * @returns {Promise} Resolves after faces are detected and RedactionAnnotations are added to document
 */
function detectAndRedactFacesFromPage(webViewerInstance, pageNumber) {
  return new Promise(resolve => {
    const doc = webViewerInstance.Core.documentViewer.getDocument();
    const pageInfo = doc.getPageInfo(pageNumber);
    const displaySize = { width: pageInfo.width, height: pageInfo.height };
    // face-api.js is detecting faces from images, so we need to convert current page to a canvas which then can
    // be converted to an image.
    doc.loadCanvas({
      pageNumber,
      zoom: 0.5, // Scale page size down to allow faster image processing
      drawComplete: function drawComplete(canvas) {
        convertCanvasToImage(canvas).then(async image => {
          const detections = await faceapi.detectAllFaces(
            image,
            new faceapi.SsdMobilenetv1Options({
              minConfidence: 0.4,
              maxResults: 300,
            })
          );
          // As we scaled our image, we need to resize faces back to the original page size
          const resizedDetections = faceapi.resizeResults(detections, displaySize);
          createFaceRedactionAnnotation(webViewerInstance, pageNumber, resizedDetections);
          resolve();
        });
      },
    });
  });
}

/**
 * onClick handler factory for redact faces button. Creates new onClick handler that encloses
 * webViewer instance inside closure.
 *
 * @param {WebViewerInstance} webViewerInstance current instance on WebViewer
 * @returns {function} returns async click handler for redact faces button
 */
function onRedactFacesButtonClickFactory(webViewerInstance) {
  return async function onRedactFacesButtonClick() {
    webViewerInstance.UI.closeElements(['redact-faces-instructions-modal']);
    const doc = webViewerInstance.Core.documentViewer.getDocument();
    const numberOfPages = doc.getPageCount();
    const { sendPageProcessing, showProgress, hideProgress } = createProgress(numberOfPages);
    showProgress();
    for (let pageNumber = 1; pageNumber <= numberOfPages; pageNumber++) {
      sendPageProcessing();
      await detectAndRedactFacesFromPage(webViewerInstance, pageNumber);
    }
    hideProgress();
  };
}

// Load face-api.js model
faceapi.nets.ssdMobilenetv1.loadFromUri('https://pdftron.s3.amazonaws.com/downloads/pl/face-redaction-models');

function createInstructionsModal(buttonClickHandler) {
  const instructionModal = {
    dataElement: 'redact-faces-instructions-modal',
    disableBackdropClick: true,
    disableEscapeKeyDown: true,
    render: function renderCustomModal() {
      const container = document.createElement('div');
      container.classList.add('redact-faces-instructions');
      const textContainer = document.createElement('div');
      textContainer.innerHTML = "Click 'Redact Faces' button below to start face redaction process.";
      const button = document.createElement('button');
      button.innerHTML = 'Redact Faces';
      button.addEventListener('click', buttonClickHandler);
      container.appendChild(textContainer);
      container.appendChild(button);
      return container;
    },
  };
  return instructionModal;
}

WebViewer(
  {
    path: '../../../lib',
    css: 'instruction-modal.css',
    fullAPI: true,
    enableRedaction: true,
    enableFilePicker: true,
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/pdftron-face-refaction-sample.pdf',
  },
  document.getElementById('viewer')
).then(webViewerInstance => {
  const FitMode = webViewerInstance.UI.FitMode;
  webViewerInstance.UI.setFitMode(FitMode.FitWidth);
  const onRedactFacesButtonClick = onRedactFacesButtonClickFactory(webViewerInstance);

  const documentViewer = webViewerInstance.Core.documentViewer;
  function onDocumentLoaded() {
    const instructionModal = createInstructionsModal(onRedactFacesButtonClick);
    webViewerInstance.UI.setCustomModal(instructionModal);
    webViewerInstance.UI.openElements(['redact-faces-instructions-modal']);
  }
  documentViewer.addEventListener('documentLoaded', onDocumentLoaded);
});
