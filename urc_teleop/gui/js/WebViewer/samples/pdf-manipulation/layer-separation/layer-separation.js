// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.openElements: https://www.pdftron.com/api/web/UI.html#openElements__anchor
// @link UI.closeElements: https://www.pdftron.com/api/web/UI.html#closeElements__anchor

// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html
// @link DocumentViewer.refreshAll: https://www.pdftron.com/api/web/Core.DocumentViewer.html#refreshAll__anchor
// @link DocumentViewer.updateView: https://www.pdftron.com/api/web/Core.DocumentViewer.html#updateView__anchor

// @link Document: https://www.pdftron.com/api/web/Core.Document.html
// @link Document.getLayersArray: https://www.pdftron.com/api/web/Core.Document.html#getLayersArray__anchor
// @link Document.setLayersArray: https://www.pdftron.com/api/web/Core.Document.html#setLayersArray__anchor

WebViewer(
  {
    path: '../../../lib',
    initialDoc: '../../../samples/files/construction-drawing-final.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const { documentViewer } = instance.Core;
  instance.UI.openElements(['leftPanel']);
  instance.UI.setActiveLeftPanel('layersPanel');
  documentViewer.addEventListener('pageComplete', () => {
    instance.UI.closeElements(['loadingModal']);
  });
});
