(function(exports) {
  const RGBA_INDEX = {
    R: 0,
    G: 1,
    B: 2,
    A: 3,
  };

  const NUMBER_OF_COLOR_CHANNELS = Object.keys(RGBA_INDEX).length;

  const MAX_HEX_VALUE = 255;

  function isPixelWhite(red, green, blue, alpha) {
    if (alpha === null || alpha === undefined || alpha === 0) {
      return true;
    }
    return red === MAX_HEX_VALUE && green === MAX_HEX_VALUE && blue === MAX_HEX_VALUE;
  }

  function isPixelColorSame(color1, color2) {
    return color1 && color2 && color1.r === color2.r && color1.g === color2.g && color1.b === color2.b && color1.a === color2.a;
  }

  function getCoordsByImageDataIndex(imageDataIndex, width) {
    const pixelDataStartIndex = Math.floor(imageDataIndex / NUMBER_OF_COLOR_CHANNELS);
    return {
      x: pixelDataStartIndex % width,
      y: Math.floor(pixelDataStartIndex / width),
    };
  }

  function getImageDataIndexByCoordinates(coordinates, width) {
    return (coordinates.y * width + coordinates.x) * NUMBER_OF_COLOR_CHANNELS;
  }

  function findAverage(values) {
    if (!values || values.length === 0) {
      return 0;
    }
    return values.reduce((accumulator, current) => accumulator + current) / values.length;
  }

  function updatePixelRGBAByDocumentDataIndex(documentData, imageDataIndex, { r, g, b, a }) {
    documentData[imageDataIndex + RGBA_INDEX.R] = r;
    documentData[imageDataIndex + RGBA_INDEX.G] = g;
    documentData[imageDataIndex + RGBA_INDEX.B] = b;
    documentData[imageDataIndex + RGBA_INDEX.A] = a;
    return documentData;
  }

  function getRGBAFromDocumentDataAtIndex(documentData, imageDataIndex) {
    return [documentData[imageDataIndex + RGBA_INDEX.R], documentData[imageDataIndex + RGBA_INDEX.G], documentData[imageDataIndex + RGBA_INDEX.B], documentData[imageDataIndex + RGBA_INDEX.A]];
  }

  const CanvasHelper = {
    transformImageData: function(imageDataWidth, imageDataHeight, canvas, transformationMatrixToApplyForCanvas) {
      const transformationMatrixArray = transformationMatrixToApplyForCanvas.toTransform();

      const imageDataInfo = this.getImageDataByDocumentCanvas(canvas);
      const inMemoryCanvas = document.createElement('canvas');
      const inMemoryCanvasContext = inMemoryCanvas.getContext('2d');
      inMemoryCanvas.width = imageDataWidth;
      inMemoryCanvas.height = imageDataHeight;
      inMemoryCanvasContext.setTransform(1, 0, 0, 1, 0, 0);
      inMemoryCanvasContext.clearRect(0, 0, inMemoryCanvas.width, inMemoryCanvas.height);

      const tempCanvas = document.createElement('canvas');
      const tempCanvasContext = tempCanvas.getContext('2d');
      tempCanvas.width = imageDataInfo.width;
      tempCanvas.height = imageDataInfo.height;
      tempCanvasContext.putImageData(imageDataInfo.imageData, 0, 0);
      inMemoryCanvasContext.setTransform(
        transformationMatrixArray[0],
        transformationMatrixArray[1],
        transformationMatrixArray[2],
        transformationMatrixArray[3],
        transformationMatrixArray[4],
        transformationMatrixArray[5]
      );
      inMemoryCanvasContext.drawImage(tempCanvas, 0, 0);
      inMemoryCanvasContext.setTransform(1, 0, 0, 1, 0, 0);
      return inMemoryCanvasContext.getImageData(0, 0, inMemoryCanvas.width, inMemoryCanvas.height);
    },
    getImageDataByDocumentCanvas: function(canvas) {
      const canvasContext = canvas.getContext('2d');
      const imageData = canvasContext.getImageData(0, 0, canvas.width, canvas.height);
      return {
        imageData,
        width: canvas.width,
        height: canvas.height,
      };
    },
    // this pixel appears in both first and second doc, just as diff color
    handleDifferentPixelColor: function(sourceDocumentRGBA, targetDocumentRGBA, shouldDiff, targetDocumentOpacity, sourceDocumentOpacity) {
      if (shouldDiff) {
        const sourceDocumentAverageLightnessColor = findAverage([sourceDocumentRGBA[RGBA_INDEX.R], sourceDocumentRGBA[RGBA_INDEX.G], sourceDocumentRGBA[RGBA_INDEX.B]]);
        const targetDocumentAverageLightnessColor = findAverage([targetDocumentRGBA[RGBA_INDEX.R], targetDocumentRGBA[RGBA_INDEX.G], targetDocumentRGBA[RGBA_INDEX.B]]);

        const lightnessAverage = findAverage([sourceDocumentAverageLightnessColor, targetDocumentAverageLightnessColor]);

        // color it magenta-ish based on color difference
        const colorDifference =
          Math.abs(targetDocumentRGBA[RGBA_INDEX.R] - sourceDocumentRGBA[RGBA_INDEX.R]) +
          Math.abs(targetDocumentRGBA[RGBA_INDEX.G] - sourceDocumentRGBA[RGBA_INDEX.G]) +
          Math.abs(targetDocumentRGBA[RGBA_INDEX.B] - sourceDocumentRGBA[RGBA_INDEX.B]);

        const colorDifferencePercentage = colorDifference / (MAX_HEX_VALUE * 3);
        const colorDifferenceAdjustment = lightnessAverage * colorDifferencePercentage;
        const primaryMagentaValueAdjustment = lightnessAverage + colorDifferenceAdjustment;
        const opacity = Math.max(Math.round(MAX_HEX_VALUE * sourceDocumentOpacity), Math.round(MAX_HEX_VALUE * targetDocumentOpacity));
        // depending on color difference, the color will be more/less magenta with more/less hints of gray
        return {
          r: primaryMagentaValueAdjustment,
          g: lightnessAverage - colorDifferenceAdjustment,
          b: primaryMagentaValueAdjustment,
          a: opacity,
        };
      }
      if (targetDocumentOpacity > sourceDocumentOpacity) {
        // blend both pixels together
        const mixFactor = sourceDocumentOpacity;
        return {
          r: sourceDocumentRGBA[RGBA_INDEX.R] * mixFactor + targetDocumentRGBA[RGBA_INDEX.R] * (1 - mixFactor),
          g: sourceDocumentRGBA[RGBA_INDEX.G] * mixFactor + targetDocumentRGBA[RGBA_INDEX.G] * (1 - mixFactor),
          b: sourceDocumentRGBA[RGBA_INDEX.B] * mixFactor + targetDocumentRGBA[RGBA_INDEX.B] * (1 - mixFactor),
          a: Math.round(255 * targetDocumentOpacity),
        };
      }
      return {
        r: targetDocumentRGBA[RGBA_INDEX.R],
        g: targetDocumentRGBA[RGBA_INDEX.G],
        b: targetDocumentRGBA[RGBA_INDEX.B],
        a: Math.round(255 * sourceDocumentOpacity),
      };
    },
    combinePixels: function(targetImageData, sourceImageData, sourceDocumentOpacity, targetDocumentOpacity, canvasMultiplier, showAsDiff) {
      const targetDocData = targetImageData ? targetImageData.data : undefined;
      const sourceDocData = sourceImageData ? sourceImageData.data : undefined;

      const resultCanvas = exports.Util.createCanvas(Math.max(sourceImageData.width, targetImageData.width), Math.max(sourceImageData.height, targetImageData.height), canvasMultiplier);
      const resultImageData = resultCanvas.getContext('2d').createImageData(resultCanvas.width, resultCanvas.height);
      resultImageData.data.set(targetDocData);

      for (let targetDocIndex = 0; targetDocIndex < targetDocData.length; targetDocIndex += NUMBER_OF_COLOR_CHANNELS) {
        // convert flat array into x,y coordinates
        const targetDocCanvasCoords = getCoordsByImageDataIndex(targetDocIndex, targetImageData.width);
        // gind the index in the other array buffer based on xy coordinate; this is incase they are different size
        const sourceDocIndex = getImageDataIndexByCoordinates(targetDocCanvasCoords, sourceImageData.width);

        const targetDocumentRGBA = getRGBAFromDocumentDataAtIndex(targetDocData, targetDocIndex);
        const sourceDocumentRGBA = getRGBAFromDocumentDataAtIndex(sourceDocData, sourceDocIndex);
        let newRGBAValues = {
          r: targetDocumentRGBA[RGBA_INDEX.R],
          g: targetDocumentRGBA[RGBA_INDEX.G],
          b: targetDocumentRGBA[RGBA_INDEX.B],
          a: targetDocumentRGBA[RGBA_INDEX.A],
        };
        if (
          isPixelWhite(sourceDocumentRGBA[RGBA_INDEX.R], sourceDocumentRGBA[RGBA_INDEX.G], sourceDocumentRGBA[RGBA_INDEX.B], sourceDocumentRGBA[RGBA_INDEX.A]) &&
          isPixelWhite(targetDocumentRGBA[RGBA_INDEX.R], targetDocumentRGBA[RGBA_INDEX.G], targetDocumentRGBA[RGBA_INDEX.B], targetDocumentRGBA[RGBA_INDEX.A])
        ) {
          // if pixel is white, make it transparent
          newRGBAValues = {
            ...newRGBAValues,
            a: 0,
          };
        } else if (
          showAsDiff &&
          isPixelColorSame(
            { r: sourceDocumentRGBA[RGBA_INDEX.R], g: sourceDocumentRGBA[RGBA_INDEX.G], b: sourceDocumentRGBA[RGBA_INDEX.B], a: sourceDocumentRGBA[RGBA_INDEX.A] },
            { r: targetDocumentRGBA[RGBA_INDEX.R], g: targetDocumentRGBA[RGBA_INDEX.G], b: targetDocumentRGBA[RGBA_INDEX.B], a: targetDocumentRGBA[RGBA_INDEX.A] }
          )
        ) {
          // if pixel values are the same, make it grey
          // halve the average again so that it falls into the range of 0 - 128 (gray)
          const lightness = findAverage([targetDocumentRGBA[RGBA_INDEX.R], targetDocumentRGBA[RGBA_INDEX.G], targetDocumentRGBA[RGBA_INDEX.B]]) / 2;
          newRGBAValues = {
            ...newRGBAValues,
            r: Math.ceil(MAX_HEX_VALUE / 2) + lightness,
            g: Math.ceil(MAX_HEX_VALUE / 2) + lightness,
            b: Math.ceil(MAX_HEX_VALUE / 2) + lightness,
          };
        } else if (targetDocCanvasCoords.y <= sourceImageData.height && targetDocCanvasCoords.x <= sourceImageData.width) {
          // https://css-tricks.com/8-digit-hex-codes/
          if (isPixelWhite(sourceDocumentRGBA[RGBA_INDEX.R], sourceDocumentRGBA[RGBA_INDEX.G], sourceDocumentRGBA[RGBA_INDEX.B], sourceDocumentRGBA[RGBA_INDEX.A])) {
            const opacity = Math.round(MAX_HEX_VALUE * targetDocumentOpacity);
            const lightness = findAverage([targetDocumentRGBA[RGBA_INDEX.R], targetDocumentRGBA[RGBA_INDEX.G], targetDocumentRGBA[RGBA_INDEX.B]]);
            newRGBAValues = {
              r: showAsDiff ? lightness : targetDocumentRGBA[RGBA_INDEX.R],
              g: showAsDiff ? lightness : targetDocumentRGBA[RGBA_INDEX.G],
              b: showAsDiff ? MAX_HEX_VALUE : targetDocumentRGBA[RGBA_INDEX.B],
              a: opacity,
            };
          } else if (isPixelWhite(targetDocumentRGBA[RGBA_INDEX.R], targetDocumentRGBA[RGBA_INDEX.G], targetDocumentRGBA[RGBA_INDEX.B], targetDocumentRGBA[RGBA_INDEX.A])) {
            const opacity = Math.round(MAX_HEX_VALUE * sourceDocumentOpacity);
            const lightness = findAverage([sourceDocumentRGBA[RGBA_INDEX.R], sourceDocumentRGBA[RGBA_INDEX.G], sourceDocumentRGBA[RGBA_INDEX.B]]);
            // if the pixel is white in second document only, color it red
            newRGBAValues = {
              r: showAsDiff ? MAX_HEX_VALUE : sourceDocumentRGBA[RGBA_INDEX.R],
              g: showAsDiff ? lightness : sourceDocumentRGBA[RGBA_INDEX.G],
              b: showAsDiff ? lightness : sourceDocumentRGBA[RGBA_INDEX.B],
              a: opacity,
            };
          } else {
            newRGBAValues = this.handleDifferentPixelColor(sourceDocumentRGBA, targetDocumentRGBA, showAsDiff, targetDocumentOpacity, sourceDocumentOpacity);
          }
        }
        updatePixelRGBAByDocumentDataIndex(resultImageData.data, targetDocIndex, newRGBAValues);
      }
      resultCanvas.getContext('2d').putImageData(resultImageData, 0, 0);
      return resultCanvas;
    },
  };

  exports.CanvasHelper = CanvasHelper;
})(window);
