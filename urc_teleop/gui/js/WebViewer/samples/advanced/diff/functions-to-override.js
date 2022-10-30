(function(exports) {
  // remove these index constants when we are no longer comparing strictly 2 documents
  exports.BASE_DOCUMENT_INDEX = 0;
  exports.DOCUMENT_TO_TRANSFORM_INDEX = 1;
  exports.DEFAULT_TRANSFORM_STATE = {
    verticalTranslation: 0,
    horizontalTranslation: 0,
    // in radians
    rotation: 0,
    scaling: 1,
  };
  exports.DEFAULT_NUDGE_STATE = {
    verticalTranslation: 0,
    horizontalTranslation: 0,
    // in radians
    rotation: 0,
    scaling: 1,
  };

  const loadAsyncCallsToCancel = {};
  // use this property as this.pages.length can't be accessed in production build
  let pageLength = 0;

  const FunctionsToOverride = {
    // need to implement some functions or else onDocumentLoaded callback in loadCanvasAsync will throw error
    // for comparing documents, we don't care about some of them, so make them return stub values
    // declare some keys as strings so that the users can use those APIs
    getLayersArray: function() {
      return Promise.resolve([]);
    },
    getBookmarks: function() {
      return Promise.resolve([]);
    },
    getPageCount: function() {
      return pageLength;
    },
    loadThumbnailAsync: function() {},
    extractXFDF: function() {
      return Promise.resolve(undefined);
    },
    loadTextData: function() {},
    unloadResources: function() {
      if (this.filesToCompare) {
        this.filesToCompare.forEach(fileToCompare => {
          fileToCompare.document.unloadResources();
        });
      }
    },
    getFileData: async function(options) {
      if (this.getPageCount() > 0) {
        let resultDocument;
        for (let i = 0; i < this.getPageCount(); i++) {
          const canvasToLoad = new Promise(resolve => {
            this.loadCanvas({
              pageNumber: i + 1,
              getZoom: () => 1,
              getPageRotation: () => 0,
              drawComplete: canvas => {
                resolve(canvas);
              },
            });
          });
          const canvasToDisplay = await canvasToLoad;
          const dataUrl = canvasToDisplay.toDataURL().replace(/^data:image\/(png|jpg);base64,/, '');
          const blob = exports.Util.base64ToBlob(dataUrl);
          if (i === 0) {
            resultDocument = await exports.Core.createDocument(blob, { extension: 'png' });
          } else {
            const document = await exports.Core.createDocument(blob, { extension: 'png' });
            await resultDocument.insertPages(document);
          }
        }
        return resultDocument.getFileData(options);
      }
      return undefined;
    },
    cancelLoadCanvas: function(id) {
      if (loadAsyncCallsToCancel[id]) {
        const cancelFunctions = loadAsyncCallsToCancel[id];
        cancelFunctions.forEach(cancelFunction => cancelFunction());
        delete loadAsyncCallsToCancel[id];
      }
    },
    loadCanvasAsync: function loadCanvasAsync({ pageNumber, getZoom, getPageRotation, drawComplete, drawProgressive, renderRect }) {
      const idToReturn = exports.uuidv4();
      const cleanedUpParameters = cleanUpParamsFromLoadCanvasAsync({ getZoom, getPageRotation, drawProgressive });
      const { zoom, pageRotation, drawProgressiveFunction } = cleanedUpParameters;
      const currentPageTransformationMatrix = this.getPageTransformationMatrix(pageNumber);
      const combinedDocumentRenderRect = renderRect;
      // render with 0 page rotation because rest of code assumes you are working with 0 page rotation
      const renderSettings = this.constructRenderSettingsForDocuments(pageNumber, zoom, 0, combinedDocumentRenderRect, [
        // order matters
        exports.Core.Math.Matrix.Identity,
        currentPageTransformationMatrix,
      ]);
      const canvasesToRender = loadCanvasesToRender(this.getDocumentsToCompare(), renderSettings, combinedDocumentRenderRect, this.dummyAnnotManagers);
      loadAsyncCallsToCancel[idToReturn] = canvasesToRender.map(canvasToRender => canvasToRender.cancel);
      Promise.all(canvasesToRender.map(canvasToRender => canvasToRender.promise)).then(async canvases => {
        const canvasMultiplier = exports.Core.getCanvasMultiplier();
        const canvasesToCompare = createValidCanvasesIfNecessary(canvases, canvasMultiplier);

        const documentsToCompare = this.getDocumentsToCompare();
        const pageNumbersToRetrieve = Object.keys(renderSettings).map(key => renderSettings[key].pageNumberToRender);
        const transformationMatriciesToApply = Object.keys(renderSettings).map(key => renderSettings[key].transformationMatrixToApply);
        const combinedBoundingBox = getCombinedViewerCoordinateBoundingBoxFromTransformationMatrix(documentsToCompare, pageNumbersToRetrieve, transformationMatriciesToApply);
        const pageScalingMatrix = new Core.Math.TransformationBuilder().scale(zoom * canvasMultiplier).getFinalTransform();
        const documentRenderRects = renderSettings.map(setting => setting.renderRect);
        const canvasesImageData = getImageDataForViewport(canvasesToCompare, combinedBoundingBox, combinedDocumentRenderRect, documentRenderRects, transformationMatriciesToApply, pageScalingMatrix);
        const documentOpacities = this.getDocumentsToCompareOpacities(pageNumber);
        // apply viewer rotation (if any) to result canvas image data
        // use canvas multiplier of 1 as it has already been scaled by this point
        const canvasMultiplierForApplingViewerRotation = 1;
        const canvasesImageDataWithViewerRotation = canvasesImageData
          .map(imageData => {
            const canvas = exports.Util.createCanvas(imageData.width, imageData.height, canvasMultiplierForApplingViewerRotation);
            canvas.getContext('2d').putImageData(imageData, 0, 0);
            return canvas;
          })
          .map(canvas => {
            let pageMatrix = window.Core.getPageMatrix(1, pageRotation, { width: canvas.width, height: canvas.height }, 0, true, canvasMultiplierForApplingViewerRotation);
            pageMatrix = {
              a: pageMatrix.m_a,
              b: pageMatrix.m_b,
              c: pageMatrix.m_c,
              d: pageMatrix.m_d,
              e: pageMatrix.m_h,
              f: pageMatrix.m_v,
            };
            let width;
            let height;
            if (pageRotation === 1 || pageRotation === 3) {
              width = canvas.height;
              height = canvas.width;
            } else {
              width = canvas.width;
              height = canvas.height;
            }
            const canvasWithViewerRotationApplied = exports.Util.createCanvas(width, height, canvasMultiplierForApplingViewerRotation);
            const ctx = canvasWithViewerRotationApplied.getContext('2d');
            ctx.setTransform(pageMatrix.a, pageMatrix.b, pageMatrix.c, pageMatrix.d, pageMatrix.e, pageMatrix.f);
            ctx.drawImage(canvas, 0, 0);
            return ctx.getImageData(0, 0, canvasWithViewerRotationApplied.width, canvasWithViewerRotationApplied.height);
          });
        const canvasToDisplay = exports.CanvasHelper.combinePixels(
          canvasesImageDataWithViewerRotation[exports.DOCUMENT_TO_TRANSFORM_INDEX],
          canvasesImageDataWithViewerRotation[exports.BASE_DOCUMENT_INDEX],
          documentOpacities[exports.DOCUMENT_TO_TRANSFORM_INDEX],
          documentOpacities[exports.BASE_DOCUMENT_INDEX],
          canvasMultiplier,
          this.isDiffing()
        );
        drawProgressiveFunction(canvasToDisplay);
        drawComplete(canvasToDisplay, pageNumber);
        delete loadAsyncCallsToCancel[idToReturn];
      });
      return idToReturn;
    },
    getDocumentCompletePromise: function() {
      const completePromises = this.getDocumentsToCompare().map(document => document.getDocumentCompletePromise());
      return Promise.all(completePromises);
    },
    loadAsync: async function({ filesToCompare, options }, onDocumentLoaded) {
      this.filesToCompare = filesToCompare;
      this.options = options;
      this.sourcePageIndexToAlignForTarget = {};
      this.dummyAnnotManagers = [];

      // use array as we want to be able to compare > 2 documents in the future
      const baseDocument = this.filesToCompare[exports.BASE_DOCUMENT_INDEX].document;
      const documentToTransform = this.filesToCompare[exports.DOCUMENT_TO_TRANSFORM_INDEX].document;
      this.alignmentPageStates = new exports.PageMatrixTransformationState();
      this.nudgePageStates = new exports.PageMatrixTransformationState();
      if (baseDocument && documentToTransform) {
        pageLength = Math.max(baseDocument.getPageCount(), documentToTransform.getPageCount());
        for (let i = 1; i <= pageLength; i++) {
          const baseDocumentInfo = baseDocument.getPageInfo(i);
          const documentToTransformInfo = documentToTransform.getPageInfo(i);
          let newPageInfo;
          let page;
          this.alignmentPageStates.setTransformationStateForPageNumber(i, exports.DEFAULT_TRANSFORM_STATE);
          this.nudgePageStates.setTransformationStateForPageNumber(i, exports.DEFAULT_NUDGE_STATE);
          if (baseDocumentInfo && documentToTransformInfo) {
            const width = Math.max(baseDocumentInfo.width, documentToTransformInfo.width);
            const height = Math.max(baseDocumentInfo.height, documentToTransformInfo.height);
            page = baseDocument.getPages()[i - 1];
            newPageInfo = createPageInfo(i, page);
            newPageInfo.width = width;
            newPageInfo.height = height;
          } else if (baseDocumentInfo) {
            page = baseDocument.getPages()[i - 1];
            newPageInfo = createPageInfo(i, page);
          } else {
            page = documentToTransform.getPages()[i - 1];
            newPageInfo = createPageInfo(i, page);
          }
          this['addPage'](newPageInfo);
        }
        this.maxViewportZoom = this.calculateMaxViewportZoom();

        if (this.shouldDiffAnnotations()) {
          this.dummyAnnotManagers = await Promise.all(
            [baseDocument, documentToTransform].map(async (documentToRender, index) => {
              const dummyDocViewer = new this.filesToCompare[index].Core.DocumentViewer();
              dummyDocViewer.setViewerElement(document.createElement('div'));
              dummyDocViewer.setScrollViewElement(document.createElement('div'));
              await dummyDocViewer.loadDocument(documentToRender);
              dummyDocViewer.enableAnnotations();
              const dummyAnnotManager = dummyDocViewer.getAnnotationManager();
              const xfdfObject = await documentToRender.extractXFDF();
              await dummyAnnotManager.importAnnotations(xfdfObject.xfdfString);
              return Promise.resolve(dummyAnnotManager);
            })
          );
        }
        onDocumentLoaded();
      }
    },
    getPageTransformationMatrix: function(pageNumber) {
      const alignmentTransformationMatrix = this.alignmentPageStates.getPageMatrixFromPageNumber(pageNumber);
      const nudgeMatrix = this.nudgePageStates.getPageMatrixFromPageNumber(pageNumber);
      const transformationMatrix = nudgeMatrix.multiply(alignmentTransformationMatrix);
      return transformationMatrix;
    },
    getDocumentsToCompare: function() {
      return this.filesToCompare ? this.filesToCompare.map(fileToCompare => fileToCompare.document) : [];
    },
    shouldResetInitialPageRotations: function() {
      return this.options && this.options.resetInitialPageRotations;
    },
    shouldDiffAnnotations: function() {
      return this.options && this.options.diffAnnotations;
    },
    isDiffing: function() {
      return this.options && this.options.shouldDiff !== undefined ? this.options.shouldDiff : true;
    },
    getDocumentsToCompareOpacities: function(pageNumber) {
      return this.filesToCompare
        ? this.filesToCompare.map(fileToCompare => {
            return fileToCompare.pageOpacities && fileToCompare.pageOpacities[pageNumber - 1] !== undefined ? fileToCompare.pageOpacities[pageNumber - 1] : 1;
          })
        : [];
    },
    updatePageSizeFromTransformationState: function(sourcePageNumber, targetPageNumber, rotation) {
      const documentsToCompare = this.getDocumentsToCompare();
      // order matters
      const pageNumbersToRetrieve = [targetPageNumber, sourcePageNumber];
      const transformationMatrix = this.getPageTransformationMatrix(targetPageNumber);
      const combinedViewerCoordBoundingBox = getCombinedViewerCoordinateBoundingBoxFromTransformationMatrix(documentsToCompare, pageNumbersToRetrieve, [
        exports.Core.Math.Matrix.Identity,
        transformationMatrix,
      ]);

      const newWidth = Math.ceil(combinedViewerCoordBoundingBox.width);
      const newHeight = Math.ceil(combinedViewerCoordBoundingBox.height);
      // set as 1 as scaling will be handled in loadCanvasAsync
      const pageScaling = 1;
      const matrix = window.Core.getPageMatrix(pageScaling, rotation, { width: newWidth, height: newHeight }, 0, true, exports.Core.getCanvasMultiplier());

      const newPageInfo = new exports.Core.PageInfo();
      newPageInfo.setFromPageData({
        width: newWidth,
        height: newHeight,
        rotation,
        id: this.getPage(targetPageNumber).id,
        matrix,
        pageNum: targetPageNumber,
      });
      newPageInfo['contentChanged'] = true;

      this.setPage(newPageInfo, targetPageNumber);
      this.maxViewportZoom = this.calculateMaxViewportZoom();
      // load canvas async is triggered as a side effect
      this.forwardEvent({
        type: 'pagesUpdated',
        data: [newPageInfo],
      });
    },
    constructRenderSettingsForDocuments: function(pageNumberToView, zoom, pageRotation, renderRect, transformationMatriciesToApply) {
      const documentToTransformPageNumber = this.getSourcePageNumberForAlignedPage(pageNumberToView);
      const scaleValues = transformationMatriciesToApply.map(tempMatrix => {
        const { scaleX } = exports.Util.decomposeMatrix(tempMatrix);
        return scaleX;
      });

      const documentRenderSettings = [
        {
          pageNumberToRender: pageNumberToView,
          pageRotation,
          zoom: zoom * scaleValues[exports.BASE_DOCUMENT_INDEX],
          transformationMatrixToApply: transformationMatriciesToApply[exports.BASE_DOCUMENT_INDEX],
          renderRect: null,
        },
        {
          pageNumberToRender: documentToTransformPageNumber,
          pageRotation,
          zoom: zoom * scaleValues[exports.DOCUMENT_TO_TRANSFORM_INDEX],
          transformationMatrixToApply: transformationMatriciesToApply[exports.DOCUMENT_TO_TRANSFORM_INDEX],
          renderRect: null,
        },
      ];

      const documentsToCompare = this.getDocumentsToCompare();
      const pageNumbersToRetrieve = documentRenderSettings.map(setting => setting.pageNumberToRender);

      const viewportsToRender = findCorrectRenderRectForDocumentsToCompare(renderRect, documentsToCompare, pageNumbersToRetrieve, transformationMatriciesToApply) || [];

      const documentRenderSettingsWithRenderRect = documentRenderSettings.map((setting, index) => ({
        ...setting,
        renderRect: viewportsToRender[index],
      }));
      return documentRenderSettingsWithRenderRect;
    },
    getSourcePageNumberForAlignedPage: function(targetPageNumber) {
      if (this.sourcePageIndexToAlignForTarget[targetPageNumber - 1] !== undefined && this.sourcePageIndexToAlignForTarget[targetPageNumber - 1] !== null) {
        return this.sourcePageIndexToAlignForTarget[targetPageNumber - 1] + 1;
      }
      return targetPageNumber;
    },
  };

  function findCorrectRenderRectForDocumentsToCompare(renderRect, documentsToCompare, pageNumbersToRetrieve, transformationMatriciesToApply) {
    if (!renderRect) {
      return undefined;
    }
    const combinedViewerCoordBoundingBox = getCombinedViewerCoordinateBoundingBoxFromTransformationMatrix(documentsToCompare, pageNumbersToRetrieve, transformationMatriciesToApply);
    const correctRenderRects = [];
    // convert it to object that is easier to work with
    const viewport = renderRectToBoundingBox(renderRect);
    for (let i = 0; i < documentsToCompare.length; i++) {
      const document = documentsToCompare[i];
      const pageNumber = pageNumbersToRetrieve[i];
      const { width, height } = document.getPageInfo(pageNumber);
      const transformedPageCorners = getTransformedPointsForPageCorners(width, height, transformationMatriciesToApply[i]);
      let viewportForDoc = findViewportForDocument(combinedViewerCoordBoundingBox, viewport, transformedPageCorners, transformationMatriciesToApply[i]);
      if (viewportForDoc) {
        // convert it back to original object format
        viewportForDoc = boundingBoxToRenderRect(viewportForDoc);
      }
      correctRenderRects.push(viewportForDoc);
    }
    return correctRenderRects;
  }

  function getCombinedViewerCoordinateBoundingBoxFromTransformationMatrix(documentsToCompare, pageNumbersToRetrieve, transformationMatriciesToApply) {
    // rotates/transforms the corner points according to the tracnsformation matrix applied to the page
    // and find bounding box to fit the newly rotated/transformed rectangle
    const [baseDocumentTransformedPageCorners, diffDocumentTransformedPageCorners] = getTransformedPageCornersFromDocumentsToCompare(
      documentsToCompare,
      pageNumbersToRetrieve,
      transformationMatriciesToApply
    );

    let combinedViewerCoordPoints = [...baseDocumentTransformedPageCorners, ...diffDocumentTransformedPageCorners];

    combinedViewerCoordPoints = combinedViewerCoordPoints.map(points => points.map(point => Math.floor(point)));
    const combinedViewerCoordBoundingBox = findBoundingBox(combinedViewerCoordPoints);
    return combinedViewerCoordBoundingBox;
  }

  function getTransformedPageCornersFromDocumentsToCompare(documentsToTransform, pageNumbersToRetrieve, transformationMatriciesToApply) {
    return documentsToTransform.map((document, index) => {
      let pageInfo = document.getPageInfo(pageNumbersToRetrieve[index]);
      if (!pageInfo) {
        // the page does not exist, create dummy information
        pageInfo = {
          width: 0,
          height: 0,
        };
      }
      let transformedPageCorners;
      if (transformationMatriciesToApply[index]) {
        const transformationMatrixToApply = transformationMatriciesToApply[index];
        const { width, height } = pageInfo;
        transformedPageCorners = getTransformedPointsForPageCorners(width, height, transformationMatrixToApply);
      }
      return transformedPageCorners;
    });
  }

  function createPageInfo(pageNum, page) {
    const newPageInfo = new exports.Core.PageInfo(page.width, page.height);
    newPageInfo['setFromPageData']({
      // syntax has to be like this because properties are accessed this way internally
      width: page.width,
      height: page.height,
      matrix: page.matrix,
      rotation: page.rotation,
      id: page.id,
      pageNum,
    });
    return newPageInfo;
  }

  function loadCanvasesToRender(documents, pageConfigurations, combinedDocumentRenderRect, annotManagers) {
    const nothingToLoad = {
      promise: Promise.resolve(undefined),
      cancel: function() {},
    };

    return documents.map((document, index) => {
      if (pageConfigurations[index]) {
        const { pageNumberToRender, pageRotation, zoom, renderRect } = pageConfigurations[index];
        // check that the document exists in current overall viewport first before trying to render it
        if (pageNumberToRender > document.getPageCount() || (combinedDocumentRenderRect && !pageConfigurations[index].renderRect)) {
          return nothingToLoad;
        }
        return getDocumentCanvas(document, pageNumberToRender, pageRotation, zoom, renderRect, annotManagers[index]);
      }
      return nothingToLoad;
    });
  }

  function getDocumentCanvas(documentToRender, pageNumberToRender, pageRotation, zoomLevel, viewportRect, annotationManager) {
    let id;
    const promise = new Promise((resolve, reject) => {
      try {
        // deep clone for now because
        // on WebViewer Core side, in getPageMatrix function, it actually alters the viewport render rect
        const renderRect = viewportRect ? { ...viewportRect, rect: [...viewportRect.rect] } : undefined;

        id = documentToRender.loadCanvas({
          pageNumber: pageNumberToRender,
          pageRotation,
          zoom: zoomLevel,
          drawComplete: async pageCanvas => {
            if (annotationManager) {
              const ctx = pageCanvas.getContext('2d');
              // ensure that annotations are rotated according to page
              // use document page rotating as the pageRotation correspond to only compareDoc's viewer rotation

              const pageRotation = exports.Util.convertToWebViewerRotationEnum(documentToRender.getPageRotation(pageNumberToRender));

              const pageInfo = documentToRender.getPageInfo(pageNumberToRender);
              if (renderRect) {
                // use matrix transformation so that annotations are drawn correctly in viewport rendering mode
                let pageWidth = pageInfo.width;
                let pageHeight = pageInfo.height;
                if (pageRotation === 1 || pageRotation === 3) {
                  pageWidth = pageInfo.height;
                  pageHeight = pageInfo.width;
                }
                let pageMatrix = window.Core.getPageMatrix(1, pageRotation, { width: pageWidth, height: pageHeight }, null, false).inverse();

                const normalizedRenderRect = window.Core.normalizeRect(pageMatrix.mult({ x: renderRect.x1, y: renderRect.y1 }), pageMatrix.mult({ x: renderRect.x2, y: renderRect.y2 }));

                pageMatrix = window.Core.getPageMatrix(zoomLevel, (pageRotation || 0) % 4, normalizedRenderRect, null, true, window.utils.getCanvasMultiplier());
                ctx.setTransform(pageMatrix.m_a, pageMatrix.m_b, pageMatrix.m_c, pageMatrix.m_d, pageMatrix.m_h, pageMatrix.m_v);
              } else {
                annotationManager.setAnnotationCanvasTransform(ctx, zoomLevel, exports.Util.convertToWebViewerRotationEnum(documentToRender.getPageRotation(pageNumberToRender)));
              }
              await annotationManager.drawAnnotations(pageNumberToRender, pageCanvas);
            }
            resolve(pageCanvas);
          },
          renderRect,
        });
      } catch (e) {
        console.error(e);
        reject(`Error occurred while loading ${document.filename} for page ${pageNumberToRender}`);
      }
    });
    return {
      promise,
      cancel: function() {
        documentToRender.cancelLoadCanvas(id);
      },
    };
  }

  function cleanUpParamsFromLoadCanvasAsync(loadAsyncParams) {
    return {
      zoom: loadAsyncParams.getZoom ? loadAsyncParams.getZoom() : 1,
      pageRotation: loadAsyncParams.getPageRotation ? loadAsyncParams.getPageRotation() : 0,
      drawProgressiveFunction: loadAsyncParams.drawProgressive ? loadAsyncParams.drawProgressive : () => {},
    };
  }

  function createValidCanvasesIfNecessary(canvases, canvasMultiplier) {
    const validCanvases = canvases.filter(canvas => canvas !== undefined);
    const { maxWidth, maxHeight } = getMaxCanvasesDimensions(validCanvases);
    return canvases.map(canvas => {
      if (!canvas) {
        canvas = exports.Util.createCanvas(maxWidth, maxHeight, canvasMultiplier);
      }
      return canvas;
    });
  }
  function getMaxCanvasesDimensions(canvases) {
    return canvases.reduce(
      (accumulator, canvas) => {
        return {
          maxWidth: Math.max(canvas.width, accumulator.maxWidth),
          maxHeight: Math.max(canvas.height, accumulator.maxHeight),
        };
      },
      { maxWidth: 0, maxHeight: 0 }
    );
  }

  function getTransformedPointsForPageCorners(width, height, transformationMatrix) {
    const pointsInViewerCoordinates = [new Core.Math.Point(0, 0), new Core.Math.Point(width, 0), new Core.Math.Point(width, height), new Core.Math.Point(0, height)];
    const transformedPoints = [];
    for (let i = 0; i < pointsInViewerCoordinates.length; i++) {
      const pointInViewerCoordinate = pointsInViewerCoordinates[i];
      const transformedPoint = transformationMatrix.multiply(pointInViewerCoordinate.toMatrix());
      transformedPoints.push([transformedPoint.get(0, 0), transformedPoint.get(1, 0)]);
    }
    return transformedPoints;
  }

  function findBoundingBox(points) {
    const boundingBox = [...points].filter(Boolean).reduce(
      (bbox, point) => {
        return {
          minX: Math.min(bbox.minX, point[0]),
          minY: Math.min(bbox.minY, point[1]),
          maxX: Math.max(bbox.maxX, point[0]),
          maxY: Math.max(bbox.maxY, point[1]),
        };
      },
      { minX: Infinity, minY: Infinity, maxX: -Infinity, maxY: -Infinity }
    );
    boundingBox.width = boundingBox.maxX - boundingBox.minX;
    boundingBox.height = boundingBox.maxY - boundingBox.minY;

    // as bounding box might have negative values (rotated clockwise) bounding box
    // offers dx,dy which is needed to translate coordinates so that they are all visible in canvas coordinates (0,0)
    // in top left corner.
    const translateToOriginalCoordinates = {
      deltaX: boundingBox.minX < 0 ? -boundingBox.minX : boundingBox.minX,
      deltaY: boundingBox.minY < 0 ? -boundingBox.minY : boundingBox.minY,
    };

    const transformationBuilder = new exports.Core.Math.TransformationBuilder();
    transformationBuilder.translate(translateToOriginalCoordinates.deltaX, translateToOriginalCoordinates.deltaY);
    boundingBox.translate = transformationBuilder.getFinalTransform();

    boundingBox.points = [
      [boundingBox.minX, boundingBox.minY], // top left
      [boundingBox.maxX, boundingBox.minY], // top right
      [boundingBox.maxX, boundingBox.maxY], // bottom right
      [boundingBox.minX, boundingBox.maxY], // bottom left
    ];

    return boundingBox;
  }

  // convenience function viewport bounding box to renderRect
  function boundingBoxToRenderRect(boundingBox) {
    return {
      width: boundingBox.width,
      height: boundingBox.height,
      x1: boundingBox.minX,
      y1: boundingBox.minY,
      x2: boundingBox.maxX,
      y2: boundingBox.maxY,
      rect: [boundingBox.minX, boundingBox.minY, boundingBox.maxX, boundingBox.maxY],
    };
  }

  // convenience function convert renderRect (viewport) to bounding box object
  function renderRectToBoundingBox(renderRect) {
    if (!renderRect) {
      return;
    }
    const minX = Math.min(renderRect.x1, renderRect.x2);
    const minY = Math.min(renderRect.y1, renderRect.y2);
    const maxX = Math.max(renderRect.x1, renderRect.x2);
    const maxY = Math.max(renderRect.y1, renderRect.y2);
    const points = [
      [minX, minY],
      [maxX, minY],
      [maxX, maxY],
      [minX, maxY],
    ];
    return findBoundingBox(points);
  }

  function getImageDataForViewport(canvases, combinedBoundingBox, combinedDocumentRenderRect, documentRenderRects, transformationMatriciesToApply, pageScalingMatrix) {
    const viewport = combinedDocumentRenderRect ? renderRectToBoundingBox(combinedDocumentRenderRect) : undefined;
    // as viewport can be anywhere in the page, this matrix will give us how translation
    // from original page coordinates. We need this to be able to render image to correct
    // place in the viewport.

    const viewportTranslationMatrix = viewport ? viewport.translate : exports.Core.Math.Matrix.Identity;

    // So far we've used page coordinates in all calculations. As image data will use page scaling (zoom and device pixel ration)
    // we scale the viewport coordinates to the canvas coordinates.
    //
    // As in our rendering viewport will be canvas' top left corner, we will translate bounding box to canvas coordinates
    // (0,0 in top left corner)

    const inverseViewportTranslationMatrix = viewportTranslationMatrix.inverse();

    const viewportBoundingBoxTransformationMatrix = pageScalingMatrix.multiply(inverseViewportTranslationMatrix);
    let viewportInCanvasCoordinatesBoundingBox;

    if (!viewport) {
      const combinedBoundingBoxPoints = combinedBoundingBox.points.map(point => {
        return new exports.Core.Math.Point(point[0], point[1]);
      });
      const transformedPoints = combinedBoundingBoxPoints.map(point => {
        const transformedPoint = pageScalingMatrix.multiply(point.toMatrix());
        return [transformedPoint.get(0, 0), transformedPoint.get(1, 0)];
      });
      viewportInCanvasCoordinatesBoundingBox = findBoundingBox(transformedPoints);
    } else {
      const viewportPoints = viewport.points.map(point => {
        return new exports.Core.Math.Point(point[0], point[1]);
      });
      const transformedPoints = viewportPoints.map(point => {
        const transformedPoint = viewportBoundingBoxTransformationMatrix.multiply(point.toMatrix());
        return [transformedPoint.get(0, 0), transformedPoint.get(1, 0)];
      });
      viewportInCanvasCoordinatesBoundingBox = findBoundingBox(transformedPoints);
    }

    const transformationsToApply = canvases.map((canvas, i) => {
      const documentViewport = documentRenderRects && documentRenderRects[i] ? renderRectToBoundingBox(documentRenderRects[i]) : undefined;
      const pageTransformationMatrix = transformationMatriciesToApply && transformationMatriciesToApply[i] ? transformationMatriciesToApply[i] : exports.Core.Math.Matrix.Identity;
      const decomposedTransformationMatrix = exports.Util.decomposeMatrix(pageTransformationMatrix);
      const documentViewportToCanvasTranslate = documentViewport ? documentViewport.translate : exports.Core.Math.Matrix.Identity;

      // This matrix builder defines how we need to transform image data so that is correctly
      // scaled, rotated, and translated to given viewport
      const transformationBuilder = new exports.Core.Math.TransformationBuilder();
      transformationBuilder.push(pageScalingMatrix.inverse());
      transformationBuilder.push(
        new exports.Core.Math.TransformationBuilder()
          .scale(decomposedTransformationMatrix.scaleX)
          .getFinalTransform()
          .inverse()
      );
      // This translation shifts document viewport (part that is visible from the base inside given viewport)
      // to viewer coordinates
      transformationBuilder.push(documentViewportToCanvasTranslate);
      transformationBuilder.push(pageTransformationMatrix);
      transformationBuilder.push(combinedBoundingBox.translate);
      transformationBuilder.push(inverseViewportTranslationMatrix);
      transformationBuilder.push(pageScalingMatrix);
      return transformationBuilder.getFinalTransform();
    });
    return canvases.map((canvas, i) => {
      return exports.CanvasHelper.transformImageData(viewportInCanvasCoordinatesBoundingBox.width, viewportInCanvasCoordinatesBoundingBox.height, canvas, transformationsToApply[i]);
    });
  }
  function findViewportForDocument(combinedBoundingBox, viewport, transformedPageCorners, transformationMatrix) {
    if (!viewport) {
      return;
    }

    const coreControlsPoints = viewport.points.map(point => {
      return new exports.Core.Math.Point(point[0], point[1]);
    });

    const inverseTranslateMatrix = combinedBoundingBox.translate.inverse();

    const viewportPoints = coreControlsPoints.map(point => {
      const transformedPoint = inverseTranslateMatrix.multiply(point.toMatrix());
      return [transformedPoint.get(0, 0), transformedPoint.get(1, 0)];
    });

    // Viewport is in combined bounding box coordinates, so this inverse reverse it to same coordinates as the document
    const viewportPolygon = window.turf.polygon([[...viewportPoints, viewportPoints[0]]]);
    const diffPagePolygon = window.turf.polygon([[...transformedPageCorners, transformedPageCorners[0]]]);
    // Find intersection of these 2 rectangles
    const intersection = window.turf.intersect(viewportPolygon, diffPagePolygon);
    // if 2 documents doesn't have intersection, we don't need to show the diff document as it is not in viewport
    if (intersection) {
      const intersectionCoordinates = intersection.geometry.coordinates[0];
      // Convert intersection to diff page coordinates that are not rotated
      const transformedPoints2 = intersectionCoordinates.map(point => {
        const tempPoint = new exports.Core.Math.Point(point[0], point[1]);
        const transformedPoint = transformationMatrix.inverse().multiply(tempPoint.toMatrix());
        return [transformedPoint.get(0, 0), transformedPoint.get(1, 0)];
      });

      // Find bounding box for this intersection. This is the rectangle we need from diff page in order to fill
      // viewport that was given to the base document
      const intersectBoundingBox = findBoundingBox(transformedPoints2);
      return intersectBoundingBox;
    }
  }

  exports.FunctionsToOverride = FunctionsToOverride;
})(window);
