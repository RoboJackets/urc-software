(function(exports) {
  function decomposeMatrix(matrix) {
    const matrixArray = matrix.toTransform();
    const paperMatrix = new exports.paper.Matrix(matrixArray[0], matrixArray[1], matrixArray[2], matrixArray[3], matrixArray[4], matrixArray[5]);

    const decomposedMatrix = paperMatrix.decompose();
    return {
      translateX: decomposedMatrix.translation.x,
      translateY: decomposedMatrix.translation.y,
      scaleX: decomposedMatrix.scaling.x,
      scaleY: decomposedMatrix.scaling.y,
      rotation: (decomposedMatrix.rotation * Math.PI) / 180,
    };
  }

  function createCanvas(width, height, canvasMultiplier) {
    const result = document.createElement('canvas');
    const resultCtx = result.getContext('2d');
    result.width = width;
    result.height = height;
    result.style.width = `${width / canvasMultiplier}px`;
    result.style.height = `${height / canvasMultiplier}px`;
    result.style.backgroundColor = 'white';
    resultCtx.fillStyle = 'white';
    return result;
  }

  function base64ToBlob(base64) {
    const binaryString = exports.atob(base64);
    const len = binaryString.length;
    const bytes = new Uint8Array(len);
    for (let i = 0; i < len; ++i) {
      bytes[i] = binaryString.charCodeAt(i);
    }
    return new Blob([bytes], { type: 'application/pdf' });
  }

  function convertToWebViewerRotationEnum(degAngle) {
    switch (degAngle) {
      case 90:
        return 1;

      case 180:
        return 2;

      case 270:
        return 3;

      default:
        return 0;
    }
  }

  exports.Util = {
    createCanvas,
    base64ToBlob,
    convertToWebViewerRotationEnum,
    decomposeMatrix,
  };
})(window);
