// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.loadDocument: https://www.pdftron.com/api/web/UI.html#loadDocument__anchor

const viewerElement = document.getElementById('viewer');

WebViewer(
  {
    path: '../../../lib',
    // in this example we are using 'all' to preload resources for office files
    // when working with only pdf, set to 'pdf' to avoid downloading unneeded resources
    preloadWorker: 'all',
  },
  viewerElement
).then(instance => {
  samplesSetup(instance);
  const preLoadFiles = ['../../../samples/files/demo.pdf', '../../../samples/files/simple-excel_2007.xlsx', '../../../samples/files/simple-word_2007.docx'];

  const documentsDiv = document.getElementById('documents');

  preLoadFiles.forEach(file => {
    const div = document.createElement('div');
    div.innerHTML = file.split('/').slice(-1)[0];

    const button = document.createElement('button');
    button.innerHTML = 'Loading';

    const list = document.createElement('li');
    list.appendChild(div);
    list.appendChild(button);

    documentsDiv.appendChild(list);

    // using this instead of 'fetch' for IE11 support
    const xhr = new XMLHttpRequest();
    xhr.open('GET', file, true);
    xhr.responseType = 'blob';
    xhr.onload = function() {
      const doc = this.response;
      if (this.status === 200) {
        button.onclick = () => {
          viewerElement.style.visibility = 'visible';
          // file name is required for office files, 'loadDocument' will assume files are pdf if there isn't a filename
          instance.UI.loadDocument(doc, { filename: file.split('/').slice(-1)[0] });
        };
        button.innerHTML = 'Open';
      }
    };
    xhr.send();
  });

  document.getElementById('toggle').addEventListener('click', () => {
    if (viewerElement.style.visibility === 'hidden') {
      viewerElement.style.visibility = 'visible';
    } else {
      viewerElement.style.visibility = 'hidden';
    }
  });
});
