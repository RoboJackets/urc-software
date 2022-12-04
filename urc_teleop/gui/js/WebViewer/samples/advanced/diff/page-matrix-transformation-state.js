(function(exports) {
  function PageMatrixTransformationState(pageStates) {
    this.pageIndexTransformationStates = pageStates || [];
  }
  PageMatrixTransformationState.prototype.setTransformationStateForPageNumber = function(pageNumber, newState) {
    this.pageIndexTransformationStates[pageNumber - 1] = newState;
  };
  PageMatrixTransformationState.prototype.getTransformationStateForPageNumber = function(pageNumber) {
    return { ...this.pageIndexTransformationStates[pageNumber - 1] };
  };
  PageMatrixTransformationState.prototype.getPageMatrixFromPageNumber = function(pageNumber) {
    const state = { ...this.pageIndexTransformationStates[pageNumber - 1] };
    const transformationBuilder = new exports.Core.Math.TransformationBuilder();
    // order of operation matters
    transformationBuilder
      // does not make sense to have a scale value of 0
      .scale(state.scaling === 0 ? 1 : state.scaling)
      .rotate(state.rotation, true)
      .translate(state.horizontalTranslation, state.verticalTranslation);

    const matrix = transformationBuilder.getFinalTransform();
    return matrix;
  };

  exports.PageMatrixTransformationState = PageMatrixTransformationState;
})(window);
