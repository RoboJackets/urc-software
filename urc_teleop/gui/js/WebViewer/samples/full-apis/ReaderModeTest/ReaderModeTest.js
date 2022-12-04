(() => {
  window.addEventListener('viewerLoaded', () => {
    const instance = window.instance;
    const parentDocument = window.parent.document;

    instance.UI.enableElements(['readerPageTransitionButton']);

    parentDocument.getElementById('select').onchange = e => {
      instance.UI.loadDocument(e.target.value);
    };

    parentDocument.getElementById('file-picker').onchange = e => {
      const file = e.target.files[0];
      if (file) {
        instance.UI.loadDocument(file);
      }
    };

    parentDocument.getElementById('url-form').onsubmit = e => {
      e.preventDefault();
      instance.UI.loadDocument(parentDocument.getElementById('url').value);
    };

    instance.Core.documentViewer.addEventListener(
      'documentLoaded',
      () => {
        instance.UI.setZoomLevel(1);
        instance.UI.toggleReaderMode();
      },
      { once: true }
    );
  });
})();
// eslint-disable-next-line spaced-comment
//# sourceURL=config.js
