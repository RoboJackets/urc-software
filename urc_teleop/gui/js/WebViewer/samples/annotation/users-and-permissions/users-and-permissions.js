// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link WebViewerInstance.openElements: https://www.pdftron.com/api/web/WebViewerInstance.html#openElements__anchor
// @link WebViewerInstance.setToolMode: https://www.pdftron.com/api/web/WebViewerInstance.html#setToolMode__anchor

// @link AnnotationManager: https://www.pdftron.com/api/web/Core.AnnotationManager.html
// @link AnnotationManager.setCurrentUser: https://www.pdftron.com/api/web/Core.AnnotationManager.html#setCurrentUser__anchor
// @link AnnotationManager.getCurrentUser: https://www.pdftron.com/api/web/Core.AnnotationManager.html#getCurrentUser__anchor
// @link AnnotationManager.setIsAdminUser: https://www.pdftron.com/api/web/Core.AnnotationManager.html#setIsAdminUser__anchor
// @link AnnotationManager.setReadOnly: https://www.pdftron.com/api/web/Core.AnnotationManager.html#setReadOnly__anchor
// @link AnnotationManager.getAnnotationsList: https://www.pdftron.com/api/web/Core.AnnotationManager.html#getAnnotationsList__anchor
// @link AnnotationManager.showAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#showAnnotations__anchor
// @link AnnotationManager.hideAnnotations: https://www.pdftron.com/api/web/Core.AnnotationManager.html#hideAnnotations__anchor

WebViewer(
  {
    path: '../../../lib',
    webviewerServerURL: 'https://demo.pdftron.com/', // comment this out to do client-side only
    initialDoc: 'https://pdftron.s3.amazonaws.com/downloads/pl/demo-annotated.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const { annotationManager } = instance.Core;
  const { openElements } = instance.UI;
  let shouldShowAnnotFromOtherUsers = true;

  const toggleVisibility = () => {
    const currentUser = annotationManager.getCurrentUser();
    const allAnnotations = annotationManager.getAnnotationsList().filter(annot => annot.Listable);
    let annotationsToShow = allAnnotations;
    annotationManager.hideAnnotations(allAnnotations);

    if (!shouldShowAnnotFromOtherUsers) {
      annotationsToShow = allAnnotations.filter(annot => annot.Author === currentUser);
    }
    annotationManager.showAnnotations(annotationsToShow);
  };

  annotationManager.setCurrentUser('Justin');
  annotationManager.promoteUserToAdmin();
  openElements(['notesPanel']);

  document.getElementById('justin').onchange = () => {
    annotationManager.setCurrentUser('Justin');
    annotationManager.promoteUserToAdmin();
    annotationManager.disableReadOnlyMode();
    toggleVisibility();
  };

  document.getElementById('sally').onchange = () => {
    annotationManager.setCurrentUser('Sally');
    annotationManager.demoteUserFromAdmin();
    annotationManager.disableReadOnlyMode();
    toggleVisibility();
  };

  document.getElementById('brian').onchange = () => {
    annotationManager.setCurrentUser('Brian');
    annotationManager.demoteUserFromAdmin();
    annotationManager.enableReadOnlyMode();
    toggleVisibility();
  };

  document.getElementById('display').onchange = e => {
    shouldShowAnnotFromOtherUsers = e.target.checked;
    toggleVisibility();
  };
});
