// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html
// @link AnnotationManager: https://www.pdftron.com/api/web/Core.AnnotationManager.html
// @link AnnotationManager.drawAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#drawAnnotations__anchor
// @link Annotations: https://www.pdftron.com/api/web/Annotations.html

WebViewer(
  {
    path: '../../../lib',
    webviewerServerURL: 'https://demo.pdftron.com/', // comment this out to do client-side only
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/form1.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const { documentViewer, annotationManager, Annotations } = instance.Core;

  documentViewer.addEventListener('documentLoaded', () => {
    const pageCount = documentViewer.getPageCount();
    const defaultStyles = Annotations.WidgetAnnotation.getCustomStyles;
    const defaultContainerStyles = Annotations.WidgetAnnotation.getContainerCustomStyles;
    const customStyles = widget => {
      if (widget instanceof Annotations.TextWidgetAnnotation) {
        if (widget.fieldName === 'f1-1') {
          return {
            'background-color': 'lightgreen',
          };
        }
        return {
          'background-color': 'lightblue',
          color: 'brown',
        };
      }
      if (widget instanceof Annotations.PushButtonWidgetAnnotation) {
        return {
          'background-color': 'red',
          color: 'white',
        };
      }
    };

    const customContainerStyles = widget => {
      if (widget instanceof Annotations.WidgetAnnotation) {
        return {
          border: '2px solid green',
        };
      }
    };

    document.getElementById('form').onchange = e => {
      if (e.target.id === 'custom') {
        // Change styles for widget annotations
        Annotations.WidgetAnnotation.getCustomStyles = customStyles;
        Annotations.WidgetAnnotation.getContainerCustomStyles = customContainerStyles;
      } else {
        Annotations.WidgetAnnotation.getCustomStyles = defaultStyles;
        Annotations.WidgetAnnotation.getContainerCustomStyles = defaultContainerStyles;
      }
      for (let i = 0; i < pageCount; i++) {
        // Redraw canvas
        annotationManager.drawAnnotations(i + 1, null, true);
      }
    };
  });
});
