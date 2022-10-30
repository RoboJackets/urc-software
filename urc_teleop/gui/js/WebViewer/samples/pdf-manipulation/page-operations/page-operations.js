// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html

// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html

// @link Document: https://www.pdftron.com/api/web/Core.Document.html
// @link Document.getPageInfo: https://www.pdftron.com/api/web/Core.Document.html#getPageInfo__anchor
// @link Document.rotatePages: https://www.pdftron.com/api/web/Core.Document.html#rotatePages__anchor
// @link Document.cropPages: https://www.pdftron.com/api/web/Core.Document.html#cropPages__anchor
// @link Document.getPageCount: https://www.pdftron.com/api/web/Core.Document.html#getPageCount__anchor
// @link Document.removePages: https://www.pdftron.com/api/web/Core.Document.html#removePages__anchor
// @link Document.movePages: https://www.pdftron.com/api/web/Core.Document.html#movePages__anchor
// @link Document.insertBlankPages: https://www.pdftron.com/api/web/Core.Document.html#insertBlankPages__anchor

// @link Core: https://www.pdftron.com/api/web/Core.html

// @link partRetriever: https://www.pdftron.com/api/web/PartRetrievers.html
/* global saveAs */
WebViewer(
  {
    path: '../../../lib',
    useDownloader: false,
    initialDoc: '../../../samples/files/demo.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const { documentViewer, PageRotation, annotationManager, createDocument } = instance.Core;

  documentViewer.addEventListener('documentLoaded', () => {
    const doc = documentViewer.getDocument();

    const editDropdown = document.getElementById('edit');
    const moveFromDropdown = document.getElementById('move-from');
    const moveToDropdown = document.getElementById('move-to');
    const insertAtDropdown = document.getElementById('insert-at');
    const extractAtList = document.getElementById('extract-list');
    const rotateButton = document.getElementById('rotate');
    const cropButton = document.getElementById('crop');
    const deleteButton = document.getElementById('delete');
    const moveButton = document.getElementById('move');
    const insertButton = document.getElementById('insert');
    const extractButton = document.getElementById('extract');
    const filePickerButton = document.getElementById('file-picker');

    // Updates page dropdowns when page count changes
    const updatePages = pageCount => {
      editDropdown.innerHTML = '';
      moveFromDropdown.innerHTML = '';
      moveToDropdown.innerHTML = '';
      insertAtDropdown.innerHTML = '';
      extractAtList.value = pageCount > 1 ? `1-${pageCount}` : 1;

      let i;
      let option;
      for (i = 0; i < pageCount; i++) {
        option = document.createElement('option');
        option.innerHTML = i + 1;
        editDropdown.appendChild(option);
        moveFromDropdown.appendChild(option.cloneNode(true));
        moveToDropdown.appendChild(option.cloneNode(true));
        insertAtDropdown.appendChild(option.cloneNode(true));
      }

      const clonedOption = option.cloneNode(true);
      clonedOption.innerHTML = i + 1;
      insertAtDropdown.appendChild(clonedOption);
    };

    rotateButton.onclick = () => {
      // Rotate pages
      doc.rotatePages([Number(editDropdown.value)], PageRotation.E_90);
    };

    cropButton.onclick = () => {
      // Crop pages
      doc.cropPages([Number(editDropdown.value)], 40, 40, 40, 40);
    };

    deleteButton.onclick = () => {
      const newPageCount = doc.getPageCount() - 1;
      // Delete pages
      doc.removePages([Number(editDropdown.value)]);
      updatePages(newPageCount);
    };

    moveButton.onclick = () => {
      const pageFrom = Number(moveFromDropdown.value);
      let pageTo = Number(moveToDropdown.value);
      if (pageFrom < pageTo) {
        pageTo++;
      }

      // Move pages
      doc.movePages([pageFrom], pageTo);
    };

    insertButton.onclick = () => {
      const info = doc.getPageInfo(1);
      const width = info.width;
      const height = info.height;
      const newPageCount = doc.getPageCount() + 1;
      // Insert blank pages
      doc.insertBlankPages([Number(insertAtDropdown.value)], width, height);
      updatePages(newPageCount);
    };

    extractButton.onclick = async function() {
      extractAtList.setCustomValidity('');
      if (!extractAtList.checkValidity()) {
        extractAtList.reportValidity();
        return; // exit since invalid input
      }
      const pagesToExtract = [];
      const pageCount = doc.getPageCount();
      extractAtList.value.split(',').forEach(group => {
        const range = group.split('-');
        const start = Number(range[0]);
        let end = Number(range.length === 1 ? range[0] : range[1]);
        if (end > pageCount) {
          end = pageCount;
        }
        for (let i = start; i <= end; i++) {
          pagesToExtract.push(i);
        }
      });
      const annotList = annotationManager.getAnnotationsList().filter(annot => pagesToExtract.indexOf(annot.PageNumber) > -1);
      const xfdfString = await annotationManager.exportAnnotations({ annotList });
      const data = await doc.extractPages(pagesToExtract, xfdfString);
      const arr = new Uint8Array(data);
      const blob = new Blob([arr], { type: 'application/pdf' });
      saveAs(blob, 'extracted.pdf');
    };

    extractAtList.oninvalid = function() {
      extractAtList.setCustomValidity('Should only contain valid page numbers, commas, or dashes ex 1,2,3-5');
    };

    filePickerButton.onchange = e => {
      const file = e.target.files[0];
      createDocument(file, {} /* , license key here */).then(newDoc => {
        const pages = [];
        for (let i = 0; i < newDoc.getPageCount(); i++) {
          pages.push(i + 1);
        }
        const newPageCount = doc.getPageCount() + newDoc.getPageCount();
        // Insert (merge) pages
        doc.insertPages(newDoc, pages, doc.getPageCount() + 1);
        updatePages(newPageCount);
      });
    };

    updatePages(doc.getPageCount());
  });
});
