(function(exports) {
  let eventHandlersSetup = false;
  let _isInAlignmentMode = false;
  let basePanelAnnotation;
  let overlayPanelAnnotation;

  function alignPages(onAlignPressedCallback) {
    if (basePanelAnnotation && overlayPanelAnnotation) {
      onAlignPressedCallback(
        basePanelAnnotation.Start,
        basePanelAnnotation.End,
        overlayPanelAnnotation.Start,
        overlayPanelAnnotation.End,
        basePanelAnnotation.PageNumber,
        overlayPanelAnnotation.PageNumber
      );
    }
  }

  function isInAlignmentMode() {
    return _isInAlignmentMode;
  }

  function toggleAlignmentMode(basePanelInstance, overlayPanelInstance, alignmentModeButton, onEnterAlignmentMode, onExitAlignmentMode) {
    if (!_isInAlignmentMode) {
      _isInAlignmentMode = true;
      alignmentModeButton.textContent = 'Leave Alignment Mode';

      basePanelInstance.UI.setToolMode('AnnotationCreateArrow');
      overlayPanelInstance.UI.setToolMode('AnnotationCreateArrow');
      if (onEnterAlignmentMode) {
        onEnterAlignmentMode();
      }
    } else {
      _isInAlignmentMode = false;
      alignmentModeButton.textContent = 'Enter Alignment Mode';
      basePanelInstance.UI.setToolMode('AnnotationEdit');
      overlayPanelInstance.UI.setToolMode('AnnotationEdit');
      basePanelInstance.Core.documentViewer
        .getAnnotationManager()
        .deleteAnnotations(basePanelInstance.Core.documentViewer.getAnnotationManager().getAnnotationsList(), { imported: true, force: true });
      overlayPanelInstance.Core.documentViewer
        .getAnnotationManager()
        .deleteAnnotations(overlayPanelInstance.Core.documentViewer.getAnnotationManager().getAnnotationsList(), { imported: true, force: true });
      basePanelAnnotation = undefined;
      overlayPanelAnnotation = undefined;
      if (onExitAlignmentMode) {
        onExitAlignmentMode();
      }
    }
  }

  function initializeDiffAlignmentToolHandlers(basePanelInstance, overlayPanelInstance, onAlignPressedCallback, onEnterAlignmentMode, onExitAlignmentMode) {
    basePanelAnnotation = undefined;
    overlayPanelAnnotation = undefined;

    const alignmentModeButton = document.getElementById('toggle-alignment-mode');

    if (_isInAlignmentMode) {
      toggleAlignmentMode(basePanelInstance, overlayPanelInstance, alignmentModeButton, onEnterAlignmentMode, onExitAlignmentMode);
    }

    if (!eventHandlersSetup) {
      eventHandlersSetup = true;
      basePanelInstance.Core.documentViewer.getTool('AnnotationCreateArrow').addEventListener('annotationAdded', annotation => {
        // after alignment annotation is added in the left viewer
        if (basePanelAnnotation) {
          basePanelInstance.Core.documentViewer.getAnnotationManager().deleteAnnotation(basePanelAnnotation, { imported: false, force: true });
        }
        annotation.ReadOnly = true;
        basePanelAnnotation = annotation;
        alignPages(onAlignPressedCallback);
      });

      overlayPanelInstance.Core.documentViewer.getTool('AnnotationCreateArrow').addEventListener('annotationAdded', annotation => {
        // after alignment annotation is added in the right viewer
        if (overlayPanelAnnotation) {
          overlayPanelInstance.Core.documentViewer.getAnnotationManager().deleteAnnotation(overlayPanelAnnotation, { imported: false, force: true });
        }
        annotation.ReadOnly = true;
        overlayPanelAnnotation = annotation;
        alignPages(onAlignPressedCallback);
      });

      alignmentModeButton.addEventListener('click', () => {
        toggleAlignmentMode(basePanelInstance, overlayPanelInstance, alignmentModeButton, onEnterAlignmentMode, onExitAlignmentMode);
      });
      document.getElementById('enable-snap-mode').addEventListener('change', event => {
        const enableSnapMode = event.target.checked;
        basePanelInstance.Core.documentViewer.getTool('AnnotationCreateArrow').setSnapMode(enableSnapMode ? basePanelInstance.Core.documentViewer.SnapMode.DEFAULT : null);
        overlayPanelInstance.Core.documentViewer.getTool('AnnotationCreateArrow').setSnapMode(enableSnapMode ? overlayPanelInstance.Core.documentViewer.SnapMode.DEFAULT : null);
      });
    }
  }
  exports.DiffAlignmentTool = {
    initializeDiffAlignmentToolHandlers,
    isInAlignmentMode,
  };
})(window);
