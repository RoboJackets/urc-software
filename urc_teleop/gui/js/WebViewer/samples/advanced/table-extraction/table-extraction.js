// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.loadDocument: https://www.pdftron.com/api/web/UI.html#loadDocument__anchor

WebViewer(
  {
    path: '../../../lib',
    initialDoc: '../../files/table.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);

  const { annotManager, docViewer } = instance;

  docViewer.on('documentLoaded', async () => {
    const doc = docViewer.getDocument();
    const data = await doc.getFileData();
    const fileName = doc.getFilename();
    const arr = new Uint8Array(data);
    const file = new File([arr], fileName, { type: 'application/pdf' });
    const { xfdf } = await extractTableData(file);

    annotManager.importAnnotations(xfdf);
  });

  document.getElementById('file-picker').onchange = async e => {
    const file = e.target.files[0];
    if (file) {
      docViewer.loadDocument(file);
    }
  };

  async function extractTableData(file) {
    const response = await fetch('https://ai-serve.pdftron.com/extract/predict', {
      method: 'POST',
      body: file,
      headers: {
        'File-Name': file.name || 'test_pdf.pdf',
        'Content-Type': 'application/json',
      },
    });

    const data = await response.json();
    const { xfdf, html } = data;

    return { xfdf, html };
  }
});
