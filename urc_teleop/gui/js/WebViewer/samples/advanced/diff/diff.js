// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.loadDocument: https://www.pdftron.com/api/web/UI.html#loadDocument__anchor

// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html
// @link DocumentViewer.getViewportRegionRect: https://www.pdftron.com/api/web/Core.DocumentViewer.html#getViewportRegionRect__anchor
// @link DocumentViewer.getCurrentPage: https://www.pdftron.com/api/web/Core.DocumentViewer.html#getCurrentPage__anchor

// @link Core: https://www.pdftron.com/api/web/Core.html
// @link PartRetrievers: https://www.pdftron.com/api/web/PartRetrievers.html

// @link Document: https://www.pdftron.com/api/web/Core.Document.html
// @link Document.loadAsync: https://www.pdftron.com/api/web/Core.Document.html#loadAsync__anchor
// @link Document.cancelLoadCanvas: https://www.pdftron.com/api/web/Core.Document.html#cancelLoadCanvas__anchor

// Workaround while WebViewer does not have an API to check if a document is loaded or not.
let isLoading = false;

(function(exports) {
  const mainCore = Core;
  mainCore.setWorkerPath('../../../lib/core');

  const BASE_PANEL_DOC_INDEX = 0;
  const OVERLAY_PANEL_DOC_INDEX = 1;

  let originalScroller = null;
  let scrollTimeout;

  let pdfWorkerTransportPromise;
  let officeWorkerTransportPromise;

  const viewers = [];
  const instances = {};

  const PANEL_IDS = {
    BASE_PANEL: 'basePanel',
    MIDDLE_PANEL: 'resultPanel',
    OVERLAY_PANEL: 'overlayPanel',
  };

  const VIEWER_IDS = [{ panel: PANEL_IDS.BASE_PANEL }, { panel: PANEL_IDS.MIDDLE_PANEL }, { panel: PANEL_IDS.OVERLAY_PANEL }];

  const TRANSFORMATION_DELTA = 1;

  // Normally setTimout(...., 0) will work, however since IE can be slow, use a longer timeout to give more time for WebViewer to perform operations
  const timeoutForIE = 50;

  function getDocumentObject(panelId) {
    return instances[panelId].instance.Core.documentViewer.getDocument();
  }

  function getDocumentViewerObject(panelId) {
    return instances[panelId].instance.Core.documentViewer;
  }

  function onOpacitySliderValueChanged() {
    let baseDocOpacity = 1;
    let overlayDocOpacity = 1;

    if (exports.DiffOverlaySlider.isEnabled()) {
      const value = exports.DiffOverlaySlider.getValue();
      baseDocOpacity = 1 - value;
      overlayDocOpacity = value;
    }

    const compareDocs = getDocumentObject(PANEL_IDS.MIDDLE_PANEL);
    const basePanelDocCurrentPage = getDocumentViewerObject(PANEL_IDS.BASE_PANEL).getCurrentPage();
    const overlayPanelDocCurrentPage = getDocumentViewerObject(PANEL_IDS.OVERLAY_PANEL).getCurrentPage();
    compareDocs.setDocumentPageOpacity(BASE_PANEL_DOC_INDEX, basePanelDocCurrentPage, baseDocOpacity);
    compareDocs.setDocumentPageOpacity(OVERLAY_PANEL_DOC_INDEX, overlayPanelDocCurrentPage, overlayDocOpacity);
  }

  function onNudgeToolPressed(nudgeDirection) {
    const compareDocs = getDocumentObject(PANEL_IDS.MIDDLE_PANEL);
    const currPageNumber = getDocumentViewerObject(PANEL_IDS.MIDDLE_PANEL).getCurrentPage();
    switch (nudgeDirection) {
      case exports.NudgeTool.TRANSFORMATION_TYPE.HORIZONTAL_TRANSLATION_INC:
        compareDocs.translate('right', TRANSFORMATION_DELTA, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.HORIZONTAL_TRANSLATION_DEC:
        compareDocs.translate('left', TRANSFORMATION_DELTA, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.VERTICAL_TRANSLATION_INC:
        compareDocs.translate('up', TRANSFORMATION_DELTA, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.VERTICAL_TRANSLATION_DEC:
        compareDocs.translate('down', TRANSFORMATION_DELTA, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.ROTATION_INC:
        compareDocs.rotate((TRANSFORMATION_DELTA * Math.PI) / 180, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.ROTATION_DEC:
        compareDocs.rotate((-TRANSFORMATION_DELTA * Math.PI) / 180, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.SCALE_IN:
        compareDocs.scale(TRANSFORMATION_DELTA / 10, currPageNumber);
        break;
      case exports.NudgeTool.TRANSFORMATION_TYPE.SCALE_OUT:
        compareDocs.scale(-TRANSFORMATION_DELTA / 10, currPageNumber);
        break;
    }
  }

  // Create an instance of worker transport to share among WebViewer instances
  function getWorkerTransportPromise(path) {
    const filename = typeof path === 'object' ? path.name : path || '';
    const isOfficeFile = filename.endsWith('docx') || filename.endsWith('pptx') || filename.endsWith('xlsx');

    // replace with your license key here as it needs to be passed when instantiating the worker transport promise
    const licenseKey = undefined;

    // Use existing workers
    if (isOfficeFile && officeWorkerTransportPromise) {
      return officeWorkerTransportPromise;
    }
    if (!isOfficeFile && pdfWorkerTransportPromise) {
      return pdfWorkerTransportPromise;
    }
    const workerTransportPromise = Core.getDefaultBackendType().then(backendType => {
      if (path && isOfficeFile) {
        return Core.initOfficeWorkerTransports(backendType, {}, licenseKey);
      }
      // Use PDF worker by default
      return Core.initPDFWorkerTransports(backendType, {}, licenseKey);
    });

    if (path && isOfficeFile) {
      officeWorkerTransportPromise = workerTransportPromise;
    } else {
      pdfWorkerTransportPromise = workerTransportPromise;
    }

    return workerTransportPromise;
  }

  async function openDoc(panel, docPath) {
    await getDocumentViewerObject(panel).loadDocument(docPath);
  }

  function syncZoom(zoom) {
    if (!isLoading) {
      viewers.forEach(item => {
        const instance = instances[item.panel].instance;
        if (instance.UI.getZoomLevel() !== zoom) {
          instance.UI.setZoomLevel(zoom);
        }
      });
    }
  }

  function syncDocumentContainerScrolls(scrollLeft, scrollTop) {
    viewers.forEach(item => {
      const documentContainer = instances[item.panel].documentContainer;
      if (!documentContainer) {
        return;
      }
      if (documentContainer.scrollLeft !== scrollLeft) {
        documentContainer.scrollLeft = scrollLeft;
      }
      if (documentContainer.scrollTop !== scrollTop) {
        documentContainer.scrollTop = scrollTop;
      }
    });
  }

  function syncRotation(rotation) {
    viewers.forEach(item => {
      const documentViewer = getDocumentViewerObject(item.panel);
      if (documentViewer.getRotation() !== rotation) {
        documentViewer.setRotation(rotation);
      }
    });
  }

  function syncPageNumber(pageNumber) {
    viewers.forEach(item => {
      const documentViewer = getDocumentViewerObject(item.panel);
      if (documentViewer.getCurrentPage() !== pageNumber) {
        documentViewer.setCurrentPage(pageNumber);
      }
    });
  }

  function alignLineSegments(baseDocStartPoint, baseDocEndPoint, overlayDocStartPoint, overlayDocEndPoint, baseDocPageNumber, overlayDocPageNumber) {
    const compareDocs = getDocumentObject(PANEL_IDS.MIDDLE_PANEL);
    compareDocs.updatePageWithAlignment(overlayDocStartPoint, overlayDocEndPoint, baseDocStartPoint, baseDocEndPoint, overlayDocPageNumber, baseDocPageNumber);
  }

  function setupViewer(item) {
    return new Promise(resolve => {
      const viewerElement = document.getElementById(item.panel);

      WebViewer(
        {
          path: '../../../lib',
          css: './nudge-tool.css',
          // share a single instance of the worker transport
          workerTransportPromise: getWorkerTransportPromise(item.pdf),
          initialDoc: item.pdf || null,
          // turn on to enable snapping
          // fullAPI: true,
          disabledElements: ['layoutButtons', 'pageTransitionButtons', 'toolsButton', 'annotationPopup', 'panToolButton', 'linkButton', 'toolsOverlayCloseButton'],
        },
        viewerElement
      ).then(instance => {
        instance.UI.syncNamespaces({
          PDFNet: mainCore.PDFNet,
        });

        samplesSetup(instance);
        const { UI, Core } = instance;
        const { documentViewer } = Core;
        const { Feature, LayoutMode, FitMode } = UI;
        UI.disableFeatures([Feature.Annotations]);
        UI.setToolMode('AnnotationEdit');

        documentViewer.addEventListener('documentLoaded', () => {
          UI.setLayoutMode(LayoutMode.Single);
          UI.setFitMode(FitMode.FitWidth);

          if (item.panel !== PANEL_IDS.MIDDLE_PANEL) {
            documentViewer.getDocument().addEventListener('layersUpdated', () => {
              const midPanelDocumentViewer = getDocumentViewerObject(PANEL_IDS.MIDDLE_PANEL);
              if (getDocumentObject(PANEL_IDS.MIDDLE_PANEL)) {
                midPanelDocumentViewer.refreshAll();
                midPanelDocumentViewer.updateView();
              }
            });
          }

          const documentContainer = viewerElement.querySelector('iframe').contentDocument.querySelector('.DocumentContainer');

          // Sync all WebViewer instances when scroll changes
          documentContainer.onscroll = () => {
            if (!exports.DiffAlignmentTool.isInAlignmentMode()) {
              if (!originalScroller || originalScroller === documentContainer) {
                originalScroller = documentContainer;
                syncDocumentContainerScrolls(documentContainer.scrollLeft, documentContainer.scrollTop);
                clearTimeout(scrollTimeout);
                scrollTimeout = setTimeout(() => {
                  originalScroller = null;
                }, timeoutForIE);
              }
            }
          };

          // Update zoom value of the WebViewer instances
          documentViewer.addEventListener('zoomUpdated', zoom => {
            // zoom events will also trigger a scroll event
            // set the original scroll to be the same panel that first triggers the zoom event
            // so that scroll events are handled properly and in the correct order
            // some browsers such as Chrome do not respect the scroll event ordering correctly
            if (!originalScroller) {
              originalScroller = documentContainer;
              clearTimeout(scrollTimeout);
              scrollTimeout = setTimeout(() => {
                originalScroller = null;
              }, timeoutForIE);
            }
            if (!exports.DiffAlignmentTool.isInAlignmentMode()) {
              syncZoom(zoom);
            }
          });

          documentViewer.addEventListener('rotationUpdated', rotation => {
            syncRotation(rotation);
          });

          documentViewer.addEventListener('pageNumberUpdated', pageNumber => {
            if (!exports.DiffAlignmentTool.isInAlignmentMode()) {
              syncPageNumber(pageNumber);
            } else {
              // we are in alignment mode
              // sync up left and middle panel as they are the same document
              if (item.panel !== PANEL_IDS.OVERLAY_PANEL) {
                viewers.forEach(viewerItem => {
                  if (getDocumentViewerObject(viewerItem.panel).getCurrentPage() !== pageNumber && viewerItem.panel !== PANEL_IDS.OVERLAY_PANEL) {
                    getDocumentViewerObject(viewerItem.panel).setCurrentPage(pageNumber);
                  }
                });
              }
            }
          });

          instances[item.panel].documentContainer = documentContainer;
        });

        viewers.push(item);
        instances[item.panel] = {
          instance,
        };
        resolve();
      });
    });
  }

  function initializeWebViewerInstances(array, callback) {
    Promise.all(array.map(setupViewer)).then(() => {
      const instance = instances[PANEL_IDS.MIDDLE_PANEL].instance;
      instance.UI.disableElements(['leftPanelButton', 'searchButton', 'searchPanel', 'searchOverlay']);
      return callback();
    });
  }

  async function initialize(basePDFRelativePath, overlayPDFRelativePath) {
    isLoading = true;

    await Promise.all([openDoc(PANEL_IDS.BASE_PANEL, basePDFRelativePath), openDoc(PANEL_IDS.OVERLAY_PANEL, overlayPDFRelativePath)]);
    exports.DiffAlignmentTool.initializeDiffAlignmentToolHandlers(
      instances[PANEL_IDS.BASE_PANEL].instance,
      instances[PANEL_IDS.OVERLAY_PANEL].instance,
      alignLineSegments,
      () => {
        // do nothing on enter
      },
      () => {
        // on leave
        const currPageNumber = getDocumentViewerObject(PANEL_IDS.MIDDLE_PANEL).getCurrentPage();
        syncPageNumber(currPageNumber);
      }
    );

    const baseDocument = instances[PANEL_IDS.BASE_PANEL].instance.Core.documentViewer.getDocument();
    const overlayDocument = instances[PANEL_IDS.OVERLAY_PANEL].instance.Core.documentViewer.getDocument();

    const files = [
      // needed to pass in Core that belongs to that document for annotation diff-ing
      { document: baseDocument, Core: instances[PANEL_IDS.BASE_PANEL].instance.Core },
      { document: overlayDocument, Core: instances[PANEL_IDS.OVERLAY_PANEL].instance.Core },
    ];

    await exports.CompareDocumentManager.initialize(instances[PANEL_IDS.MIDDLE_PANEL].instance.Core, files, {
      resetInitialPageRotations: true,
      // do not allow diffing if in IE11 else it won't work
      diffAnnotations: !(exports.navigator.userAgent.indexOf('MSIE') !== -1 || exports.navigator.appVersion.indexOf('Trident/') > -1),
    });

    isLoading = false;
  }

  initializeWebViewerInstances(VIEWER_IDS, async () => {
    await initialize(`${window.location.href}../../../samples/files/test_doc_1.pdf`, `${window.location.href}../../../samples/files/test_doc_2.pdf`);
    exports.NudgeTool.initializeNudgeTool(nudgeDirection => {
      onNudgeToolPressed(nudgeDirection);
    });
    document.getElementById('enable-snap-mode').disabled = !instances[PANEL_IDS.BASE_PANEL].instance.Core.isFullPDFEnabled() && !instances[PANEL_IDS.OVERLAY_PANEL].instance.Core.isFullPDFEnabled();
  });

  document.getElementById('selectControl').onclick = async e => {
    e.preventDefault();
    const select1 = document.getElementById('select1');
    const basePDF = select1.options[select1.selectedIndex].value;
    const select2 = document.getElementById('select2');
    const pdfToOverlay = select2.options[select2.selectedIndex].value;
    await initialize(window.location.href + basePDF, window.location.href + pdfToOverlay);
  };

  document.getElementById('url-form').onsubmit = async e => {
    e.preventDefault();
    const basePDF = document.getElementById('url').value;
    const pdfToOverlay = document.getElementById('url2').value;
    await initialize(basePDF, pdfToOverlay);
  };

  document.getElementById('file-picker-form').onsubmit = async e => {
    e.preventDefault();
    const basePDF = document.forms['file-picker-form'][0].files[0];
    const pdfToOverlay = document.forms['file-picker-form'][1].files[0];
    await initialize(basePDF, pdfToOverlay);
  };

  // use change event over input as its supported in IE11
  document.getElementById('show-difference').addEventListener('change', function() {
    const shouldDiff = this.checked;
    const compareDocs = getDocumentObject(PANEL_IDS.MIDDLE_PANEL);
    compareDocs.shouldDiff(shouldDiff);
  });

  document.getElementById('enable-opacity-slider').addEventListener('change', function() {
    const isEnabled = this.checked;
    document.getElementById('opacity-slider').disabled = !isEnabled;
    exports.DiffOverlaySlider.enable(isEnabled);
    const sliderValue = document.getElementById('opacity-slider').value;
    exports.DiffOverlaySlider.setValue(+sliderValue / 100);
    onOpacitySliderValueChanged();
  });

  document.getElementById('opacity-slider').addEventListener('change', () => {
    const sliderValue = document.getElementById('opacity-slider').value;
    exports.DiffOverlaySlider.setValue(+sliderValue / 100);
    onOpacitySliderValueChanged();
  });
})(window);
