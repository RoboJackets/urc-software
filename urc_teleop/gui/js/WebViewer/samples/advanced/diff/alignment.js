(function(exports) {
  function getLineLength(startPointX, startPointY, endPointX, endPointY) {
    const deltaX = endPointX - startPointX;
    const deltaY = endPointY - startPointY;
    return Math.sqrt(deltaX * deltaX + deltaY * deltaY);
  }

  // in viewer coordinates
  function createMatrixForLineAlignment(sourceLineStartPoint, sourceLineEndPoint, targetLineStartPoint, targetLineEndPoint) {
    // https://math.stackexchange.com/questions/1544147/find-transform-matrix-that-transforms-one-line-segment-to-another
    // Observe order of operations in the visual diagram for accepted answer
    const sourceLineAngleToOrigin = Math.atan2(sourceLineEndPoint.y - sourceLineStartPoint.y, sourceLineEndPoint.x - sourceLineStartPoint.x);
    const targetLineAngleToOrigin = Math.atan2(targetLineEndPoint.y - targetLineStartPoint.y, targetLineEndPoint.x - targetLineStartPoint.x);

    // get line lengths so we know how much to scale source line by to match line length of target line
    let sourceLineLength = getLineLength(sourceLineStartPoint.x, sourceLineStartPoint.y, sourceLineEndPoint.x, sourceLineEndPoint.y);
    sourceLineLength = sourceLineLength === 0 ? 1 : sourceLineLength;
    const targetLineLength = getLineLength(targetLineStartPoint.x, targetLineStartPoint.y, targetLineEndPoint.x, targetLineEndPoint.y);
    let scaleFactor = targetLineLength / sourceLineLength;
    scaleFactor = scaleFactor === 0 ? 1 : scaleFactor;

    // order matters
    const transformationBuilder = new exports.Core.Math.TransformationBuilder();
    transformationBuilder
      .translate(-sourceLineStartPoint.x, -sourceLineStartPoint.y)
      .scale(scaleFactor)
      .rotate(-sourceLineAngleToOrigin, true)
      .rotate(targetLineAngleToOrigin, true)
      .translate(targetLineStartPoint.x, targetLineStartPoint.y);

    const matrix = transformationBuilder.getFinalTransform();
    return matrix;
  }

  exports.Alignment = {
    createMatrixForLineAlignment,
  };
})(window);
