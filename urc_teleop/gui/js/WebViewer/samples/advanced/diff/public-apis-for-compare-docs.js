(function(exports) {
  const RIGHT = 'right';
  const LEFT = 'left';
  const DOWN = 'down';
  const UP = 'up';
  /**
   * Enum direction values
   * @enum string
   */
  const DIRECTION = {
    // arbitrary values
    // just want to use old fashion set of browser compatibililty
    [RIGHT]: 1,
    [LEFT]: 2,
    [DOWN]: 3,
    [UP]: 4,
  };

  // APIs specific to compare-docs
  const PublicAPIsForCompareDocs = {
    /**
     * @typedef {Object} Point the point in viewer coordinates
     * @property {number} x the x coordinate of the point
     * @property {number} y the y coordinate of the point
     */
    /**
     * Transforms the documents being compared such that the sourceLineStartPoint and sourceLineEndPoint
     * becomes the targetLineStartPoint and targetLineEndPoit
     * @param {Point} sourceLineStartPoint the start point of the line in the source document
     * @param {Point} sourceLineEndPoint the end point of the line in the source document
     * @param {Point} targetLineStartPoint the start point of the line in the target document
     * @param {Point} targetLineEndPoint the end point of the line in the target document
     * @param {number} sourceDocPageNumber the source document page number to align
     * @param {number} targetPageNumber the target document page number to align
     */
    updatePageWithAlignment: function(sourceLineStartPoint, sourceLineEndPoint, targetLineStartPoint, targetLineEndPoint, sourceDocPageNumber, targetPageNumber) {
      if (!validatePageAlignmentIndices(this.filesToCompare, sourceDocPageNumber, targetPageNumber)) {
        return;
      }
      const targetPageIndex = targetPageNumber - 1;
      const sourceDocPageIndex = sourceDocPageNumber - 1;
      this.sourcePageIndexToAlignForTarget[targetPageIndex] = sourceDocPageIndex;
      const transformedDocumentPages = this.filesToCompare[exports.DOCUMENT_TO_TRANSFORM_INDEX].document.getPages();
      const baseDocumentPages = this.filesToCompare[exports.BASE_DOCUMENT_INDEX].document.getPages();

      const baseDocumentPage = baseDocumentPages[targetPageIndex];
      const overlayDocumentPage = transformedDocumentPages[sourceDocPageIndex];

      let transformedSourceStartPoint = sourceLineStartPoint;
      let transformedSourceEndPoint = sourceLineEndPoint;
      let transformedTargetStartPoint = targetLineStartPoint;
      let transformedTargetEndPoint = targetLineEndPoint;

      if (this.shouldResetInitialPageRotations()) {
        transformedSourceStartPoint = exports.normalizePointToZeroRotationSpace(
          sourceLineStartPoint,
          exports.Util.convertToWebViewerRotationEnum(overlayDocumentPage.rotation),
          overlayDocumentPage.width,
          overlayDocumentPage.height
        );
        transformedSourceEndPoint = exports.normalizePointToZeroRotationSpace(
          sourceLineEndPoint,
          exports.Util.convertToWebViewerRotationEnum(overlayDocumentPage.rotation),
          overlayDocumentPage.width,
          overlayDocumentPage.height
        );
        transformedTargetStartPoint = exports.normalizePointToZeroRotationSpace(
          targetLineStartPoint,
          exports.Util.convertToWebViewerRotationEnum(baseDocumentPage.rotation),
          baseDocumentPage.width,
          baseDocumentPage.height
        );
        transformedTargetEndPoint = exports.normalizePointToZeroRotationSpace(
          targetLineEndPoint,
          exports.Util.convertToWebViewerRotationEnum(baseDocumentPage.rotation),
          baseDocumentPage.width,
          baseDocumentPage.height
        );
      }
      const newState = calculateAlignmentState(transformedSourceStartPoint, transformedSourceEndPoint, transformedTargetStartPoint, transformedTargetEndPoint);
      this.alignmentPageStates.setTransformationStateForPageNumber(targetPageNumber, newState);

      this.nudgePageStates.setTransformationStateForPageNumber(targetPageNumber, exports.DEFAULT_NUDGE_STATE);

      this.updatePageSizeFromTransformationState(sourceDocPageNumber, targetPageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(targetPageNumber).rotation);
    },
    /**
     * Translate the source document by a delta value in terms of viewer coordinate
     * @param {DIRECTION} direction one of the enumeration key of DIRECTION
     * @param {number} deltaValue the number to translate by in terms of viewer coordinates
     * @param {number} pageNumber the page number of the source document
     */
    translate: function(direction, deltaValue, pageNumber) {
      if (!DIRECTION[direction]) {
        console.error(`Please pass in a valid direction: ${Object.keys(DIRECTION).join(',')}`);
      } else {
        const nudgeState = this.nudgePageStates.getTransformationStateForPageNumber(pageNumber);
        switch (direction) {
          case UP:
            nudgeState.verticalTranslation -= deltaValue;
            break;

          case DOWN:
            nudgeState.verticalTranslation += deltaValue;
            break;

          case LEFT:
            nudgeState.horizontalTranslation -= deltaValue;
            break;

          case RIGHT:
            nudgeState.horizontalTranslation += deltaValue;
            break;
        }

        this.nudgePageStates.setTransformationStateForPageNumber(pageNumber, nudgeState);
        const sourcePageNumber = this.getSourcePageNumberForAlignedPage(pageNumber);
        this.updatePageSizeFromTransformationState(sourcePageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
      }
    },
    /**
     * Scales the source document by a delta value in terms of viewer coordinate
     * @param {number} deltaValue the number to scale by
     * @param {number} pageNumber the page number of the source document
     */
    scale: function(deltaValue, pageNumber) {
      const nudgeState = this.nudgePageStates.getTransformationStateForPageNumber(pageNumber);
      nudgeState.scaling += deltaValue;
      this.nudgePageStates.setTransformationStateForPageNumber(pageNumber, nudgeState);
      const sourcePageNumber = this.getSourcePageNumberForAlignedPage(pageNumber);
      this.updatePageSizeFromTransformationState(sourcePageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
    },
    /**
     * Rotates the source document by a delta value (in radians)
     * @param {number} radianDeltaValue the angle to rotate by
     * @param {number} pageNumber the page number of the source document
     */
    rotate: function(radianDeltaValue, pageNumber) {
      const nudgeState = this.nudgePageStates.getTransformationStateForPageNumber(pageNumber);
      nudgeState.rotation += radianDeltaValue;
      nudgeState.rotation %= 2 * Math.PI;
      this.nudgePageStates.setTransformationStateForPageNumber(pageNumber, nudgeState);
      const sourcePageNumber = this.getSourcePageNumberForAlignedPage(pageNumber);
      this.updatePageSizeFromTransformationState(sourcePageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
    },
    /**
     * Resets the nudge state
     * @param {number} pageNumber the page number of the document
     */
    resetNudgedState: function(pageNumber) {
      this.nudgePageStates.setTransformationStateForPageNumber(pageNumber, exports.DEFAULT_NUDGE_STATE);
      this.updatePageSizeFromTransformationState(pageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
    },
    /**
     * Resets the alignment state
     * @param {number} pageNumber the page number of the document
     */
    resetAlignmentState: function(pageNumber) {
      this.alignmentPageStates.setTransformationStateForPageNumber(pageNumber, exports.DEFAULT_TRANSFORM_STATE);
      this.updatePageSizeFromTransformationState(pageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
    },
    /**
     * changes the opacity of a page of a document being compared
     * @param {number} documentIndex the document to alter
     * @param {number} pageNumber the page number of the document
     * @param {number} opacityValue a number between 0-1 (inclusive)
     */
    setDocumentPageOpacity: function(documentIndex, pageNumber, opacityValue) {
      if (this.filesToCompare[documentIndex] && pageNumber <= this.filesToCompare[documentIndex].document.getPageCount()) {
        if (!this.filesToCompare[documentIndex].pageOpacities) {
          this.filesToCompare[documentIndex].pageOpacities = [];
        }
        this.filesToCompare[documentIndex].pageOpacities[pageNumber - 1] = opacityValue;
        this.updatePageSizeFromTransformationState(pageNumber, pageNumber, this.shouldResetInitialPageRotations() ? 0 : this.getPage(pageNumber).rotation);
      }
    },
    /**
     * Sets the diffing mode. If true, differences in documents will be shown using certain colors
     * @param {boolean} shouldDiff boolean to denote if document differences should be shown in certain colors
     */
    shouldDiff: function(shouldDiff) {
      if (!this.options) {
        this.options = {};
      }
      this.options.shouldDiff = shouldDiff;
      this.updatePageSizeFromTransformationState(1, 1, this.shouldResetInitialPageRotations() ? 0 : this.getPage(1).rotation);
    },
    /**
     * Gets the comparison options. See CompareDocumentManager.initialize for more information.
     */
    getOptions: function() {
      return this.options;
    },
  };

  function calculateAlignmentState(sourceStartPoint, sourceEndPoint, targetStartPoint, targetEndPoint) {
    const lineAlignmentMatrix = exports.Alignment.createMatrixForLineAlignment(sourceStartPoint, sourceEndPoint, targetStartPoint, targetEndPoint);
    const decomposedMatrix = exports.Util.decomposeMatrix(lineAlignmentMatrix);
    return {
      horizontalTranslation: decomposedMatrix.translateX,
      verticalTranslation: decomposedMatrix.translateY,
      scaling: decomposedMatrix.scaleX,
      rotation: decomposedMatrix.rotation,
    };
  }

  function validatePageAlignmentIndices(filesToCompare, sourcePageNumber, targetPageNumber) {
    const transformedDocumentPages = filesToCompare[exports.DOCUMENT_TO_TRANSFORM_INDEX].document.getPages();
    const baseDocumentPages = filesToCompare[exports.BASE_DOCUMENT_INDEX].document.getPages();
    const targetPageIndex = targetPageNumber - 1;
    const sourcePageIndex = sourcePageNumber - 1;
    if (!baseDocumentPages[targetPageIndex]) {
      console.error(`page number ${targetPageNumber} does not exist for ${filesToCompare[exports.BASE_DOCUMENT_INDEX].document.getFilename()}`);
      return false;
    }

    if (!transformedDocumentPages[sourcePageIndex]) {
      console.error(`page number ${sourcePageNumber} does not exist for ${filesToCompare[exports.DOCUMENT_TO_TRANSFORM_INDEX].document.getFilename()}`);
      return false;
    }
    return true;
  }

  exports.PublicAPIsForCompareDocs = PublicAPIsForCompareDocs;
})(window);
