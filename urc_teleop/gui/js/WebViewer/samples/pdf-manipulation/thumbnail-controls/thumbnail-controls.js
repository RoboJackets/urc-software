// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html

// @link UI.enableElements: https://www.pdftron.com/api/web/UI.html#enableElements__anchor
// @link UI.enableFeatures: https://www.pdftron.com/api/web/UI.html#enableFeatures__anchor
// @link UI.selectThumbnailPages: https://www.pdftron.com/api/web/UI.html#selectThumbnailPages__anchor

// @link Core: https://www.pdftron.com/api/web/Core.html
// @link Core.initPDFWorkerTransports: https://www.pdftron.com/api/web/Core.html#.initPDFWorkerTransports__anchor

const viewers = [
  {
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/demo-annotated.pdf',
    domElement: 'leftPanel',
  },
  {
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/report.docx',
    domElement: 'rightPanel',
  },
];
let workerTransportPromise;

Core.setWorkerPath('../../../lib/core');
Core.getDefaultBackendType().then(pdfType => {
  workerTransportPromise = Core.initPDFWorkerTransports(pdfType, {});

  initializeWebViewer(viewers[0]);
  initializeWebViewer(viewers[1]);
});

const initializeWebViewer = viewer => {
  WebViewer(
    {
      path: '../../../lib',
      // since there are two instance of WebViewer, use "workerTransportPromise" so viewers can share resources
      workerTransportPromise: {
        pdf: workerTransportPromise,
      },

      // set "useDownloader" to false to the either file is loaded
      useDownloader: false,

      // can load a office documents as PDFDocument by setting "loadAsPDF"
      loadAsPDF: true,

      initialDoc: viewer.initialDoc,
    },
    document.getElementById(`${viewer.domElement}`)
  ).then(instance => {
    const { documentViewer } = instance.Core;
    const { enableFeatures, enableElements, openElements, selectThumbnailPages, loadDocument } = instance.UI;
    enableFeatures(['ThumbnailMultiselect', 'MultipleViewerMerging']);
    enableElements(['documentControl']);

    documentViewer.addEventListener('documentLoaded', () => {
      openElements(['thumbnailsPanel']);

      // select some pages
      selectThumbnailPages([1]);
    });

    document.getElementById(`${viewer.domElement}`).addEventListener('documentMerged', data => {
      // can use "documentMerged" event to track what is being merged into a document
      console.log(`From: ${data.detail.filename} pages: ${data.detail.pages}`);
    });

    // set up controls on the left side bar
    document.getElementById(`${viewer.domElement}-select`).onchange = e => {
      loadDocument(e.target.value);
    };

    document.getElementById(`${viewer.domElement}-file-picker`).onchange = e => {
      const file = e.target.files[0];

      if (file) {
        loadDocument(file);
      }
    };

    document.getElementById(`${viewer.domElement}-url-form`).onsubmit = e => {
      e.preventDefault();
      loadDocument(document.getElementById(`${viewer.domElement}-url`).value);
    };
  });
};
