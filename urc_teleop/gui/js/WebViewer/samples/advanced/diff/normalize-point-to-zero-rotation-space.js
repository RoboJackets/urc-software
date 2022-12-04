(function(exports) {
  // point is in viewer coordinate
  // transform point to zero rotation space
  // did not use transformation matrix as it was giving wrong result
  function normalizePointToZeroRotationSpace(point, sourceRotation, sourceDocumentWidth, sourceDocumentHeight) {
    let transformedPoint = point;
    let transformFunction;
    if (sourceRotation === 1) {
      transformFunction = function(pointToTransform, width) {
        const newX = width - pointToTransform.y;
        const newY = pointToTransform.x;
        return { x: newX, y: newY };
      };
      transformedPoint = transformFunction(point, sourceDocumentWidth);
    }
    if (sourceRotation === 2) {
      transformFunction = function(pointToTransform, width, height) {
        const newX = width - pointToTransform.x;
        const newY = height - pointToTransform.y;
        return { x: newX, y: newY };
      };
      transformedPoint = transformFunction(point, sourceDocumentWidth, sourceDocumentHeight);
    }
    if (sourceRotation === 3) {
      transformFunction = function(pointToTransform, width, height) {
        const newX = pointToTransform.y;
        const newY = height - pointToTransform.x;
        return { x: newX, y: newY };
      };
      transformedPoint = transformFunction(point, sourceDocumentWidth, sourceDocumentHeight);
    }
    return transformedPoint;
  }

  exports.normalizePointToZeroRotationSpace = normalizePointToZeroRotationSpace;
})(window);
