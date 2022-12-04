// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.loadDocument: https://www.pdftron.com/api/web/UI.html#loadDocument__anchor

WebViewer(
  {
    path: '../../../lib',
    initialDoc: '../../../samples/files/demo-annotated.xod',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);

  document.getElementById('select').onchange = e => {
    if (e.target.value === 'https://pdftron.s3.amazonaws.com/downloads/pl/encrypted-foobar12.xod') {
      instance.UI.loadDocument(e.target.value, {
        decrypt: instance.Core.Encryption.decrypt,
        decryptOptions: {
          p: 'foobar12',
          type: 'aes',
          error: msg => {
            alert(msg);
          },
        },
      });
    } else {
      instance.UI.loadDocument(e.target.value);
    }
  };

  document.getElementById('file-picker').onchange = e => {
    const file = e.target.files[0];
    if (file) {
      instance.UI.loadDocument(file);
    }
  };

  document.getElementById('url-form').onsubmit = e => {
    e.preventDefault();
    instance.UI.loadDocument(document.getElementById('url').value);
  };
});
