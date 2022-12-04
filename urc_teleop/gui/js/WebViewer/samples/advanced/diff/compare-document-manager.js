(function(exports) {
  const COMPARE_DOCS = 'compare-docs';

  const CompareDocument = function(filesToCompare) {
    this.filesToCompare = filesToCompare;
  };

  function isIE11() {
    return exports.navigator.userAgent.indexOf('MSIE') !== -1 || exports.navigator.appVersion.indexOf('Trident/') > -1;
  }

  const CompareDocumentManager = {
    /**
     * Initializes compare-docs and loads in the documents to compare into WebViewer
     * @param {Object} webviewerInstance the WebViewer instance
     * @param {Object[]} filesToCompare the files to compare; note that the order of the array denotes the stacking order of the documents to compare
     * @param {Object} filesToCompare[].document - an instance of a WebViewer document class
     * @param {Object} filesToCompare[].Core - an instance of the CoreControl that created the document
     * @param {number[]} filesToCompare[].pageOpacities - an array where each element is the opacity of the page where opacity has value 0-1 (inclusive)
     * @param {Object} options an object that contains options comparison options
     * @param {boolean} options.overlay boolean to denote that documents being compared should be overlayed and not diffed
     * @param {boolean} options.resetInitialPageRotations if true, all initial rotation on all pages on all documents will be treated as having a rotation of 0
     * @param {boolean} options.diffAnnotations if true, annotations on all pages on all documents will be diff-ed
     */
    initialize: async function(webviewerCoreNamespace, filesToCompare, options) {
      this.documentViewer = webviewerCoreNamespace.documentViewer;
      CompareDocument.prototype = Object.create(webviewerCoreNamespace['BaseDocument'].prototype);
      Object.assign(CompareDocument.prototype, exports.FunctionsToOverride);
      Object.assign(CompareDocument.prototype, exports.PublicAPIsForCompareDocs);
      webviewerCoreNamespace.Document.registerDocumentType(COMPARE_DOCS, CompareDocument, Object.keys(exports.PublicAPIsForCompareDocs));
      await CompareDocumentManager.loadDocumentsToCompare(filesToCompare, options);
    },
    /**
     * Loads the document to compare into WebViewer
     * Please see CompareDocumentManager.loadDocumentsToCompare for more information
     */
    loadDocumentsToCompare: function(filesToCompare = [], options = {}) {
      if (filesToCompare.length < 2) {
        throw new Error('2 files are required file comparison');
      } else if (filesToCompare.length > 2) {
        throw new Error('comparing more than 2 files is not supported for now');
      } else if (options && options.diffAnnotations) {
        if (isIE11()) {
          throw new Error('diffing annotations is not supported in IE11');
        } else if (filesToCompare.some(filesToCompare => !filesToCompare.Core)) {
          throw new Error('diffing by annotation require Core property for document being compared');
        }
      }
      return this.documentViewer['loadAsync']({ filesToCompare, options }, { type: COMPARE_DOCS });
    },
  };
  exports.CompareDocumentManager = CompareDocumentManager;
})(window);
