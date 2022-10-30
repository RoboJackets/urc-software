// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.loadDocument: https://www.pdftron.com/api/web/UI.html#loadDocument__anchor

// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html

// @link AnnotationManager: https://www.pdftron.com/api/web/Core.AnnotationManager.html
// @link AnnotationManager.addAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#addAnnotations__anchor
// @link AnnotationManager.deleteAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#deleteAnnotations__anchor
// @link AnnotationManager.selectAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#selectAnnotations__anchor
// @link AnnotationManager.getAnnotationsList: https://www.pdftron.com/api/web/Core.AnnotationManager.html#getAnnotationsList__anchor

// @link Annotations: https://www.pdftron.com/api/web/Annotations.html

// @link Document: https://www.pdftron.com/api/web/Core.Document.html
// @link Document.loadPageText: https://www.pdftron.com/api/web/Core.Document.html#loadPageText__anchor
// @link Document.getTextPosition: https://www.pdftron.com/api/web/Core.Document.html#getTextPosition__anchor

const viewerElement = document.getElementById('viewer');
WebViewer(
  {
    path: '../../../lib',
    webviewerServerURL: 'https://demo.pdftron.com/', // comment this out to do client-side only
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/legal-contract.pdf',
  },
  viewerElement
).then(instance => {
  samplesSetup(instance);
  const { documentViewer, annotationManager, Annotations } = instance.Core;

  const renderCheckBoxes = pageCount => {
    const pagesDiv = document.getElementById('pages');
    let pageNumber;
    const checkboxes = [];

    for (pageNumber = 1; pageNumber <= pageCount; pageNumber++) {
      const input = document.createElement('input');
      /* eslint-disable prefer-template */
      input.id = `page-${pageNumber}`;
      input.type = 'checkbox';
      input.checked = false;
      input.value = pageNumber;

      checkboxes.push(input);

      const label = document.createElement('label');
      label.htmlFor = `page-${pageNumber}`;
      label.innerHTML = `Page ${pageNumber}`;

      const lineBreak = document.createElement('br');

      pagesDiv.appendChild(input);
      pagesDiv.appendChild(label);
      pagesDiv.appendChild(lineBreak);
    }

    return checkboxes;
  };

  const highlightText = (searchText, pageNumber) => {
    const doc = documentViewer.getDocument();

    // gets all text on the requested page
    // see https://pdftron.com/api/web/Core.Document.html#loadPageText__anchor
    doc.loadPageText(pageNumber).then(text => {
      let textStartIndex = 0;
      let textIndex;
      const annotationPromises = [];

      // find the position of the searched text and add text highlight annotation at that location
      while ((textIndex = text.indexOf(searchText, textStartIndex)) > -1) {
        textStartIndex = textIndex + searchText.length;
        // gets quads for each of the characters from start to end index. Then,
        // resolve the annotation and return.
        // see https://pdftron.com/api/web/Core.Document.html#getTextPosition__anchor
        const annotationPromise = doc.getTextPosition(pageNumber, textIndex, textIndex + searchText.length).then(quads => {
          const annotation = new Annotations.TextHighlightAnnotation();
          annotation.Author = annotationManager.getCurrentUser();
          annotation.PageNumber = pageNumber;
          annotation.Quads = quads;
          annotation.StrokeColor = new Annotations.Color(0, 255, 255);
          return annotation;
        });
        annotationPromises.push(annotationPromise);
      }

      // Wait for all annotations to be resolved.
      Promise.all(annotationPromises).then(annotations => {
        annotationManager.addAnnotations(annotations);
        annotationManager.selectAnnotations(annotations);
      });
    });
  };

  const removeHighlightedText = pageNumber => {
    const annotations = annotationManager.getAnnotationsList().filter(annotation => {
      return annotation.PageNumber === pageNumber;
    });
    annotationManager.deleteAnnotations(annotations);
  };

  documentViewer.addEventListener('documentLoaded', () => {
    const textInput = document.getElementById('text');
    const checkboxes = renderCheckBoxes(documentViewer.getPageCount());

    checkboxes.forEach(checkbox => {
      checkbox.addEventListener('change', () => {
        const pageNumber = Number(checkbox.value);

        if (checkbox.checked && textInput.value) {
          highlightText(textInput.value, pageNumber);
        } else {
          removeHighlightedText(pageNumber);
        }
      });
    });

    textInput.addEventListener(
      'input',
      // debounce loaded elsewhere
      // eslint-disable-next-line
      debounce(() => {
        checkboxes.forEach(checkbox => {
          const pageNumber = Number(checkbox.value);

          if (checkbox.checked) {
            removeHighlightedText(pageNumber);

            if (textInput.value) {
              highlightText(textInput.value, pageNumber);
            }
          }
        });
      }, 200)
    );

    // highlight search text in the first page by default
    checkboxes[0].checked = true;
    highlightText(textInput.value, 1);
  });
});
