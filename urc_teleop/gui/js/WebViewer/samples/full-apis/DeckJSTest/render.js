(exports => {
  const PDFNet = exports.Core.PDFNet;

  const initAll = async docurl => {
    try {
      // await exports.Core.PDFNet.initialize(); // awaits promise
      // PDFNet.beginOperation();
      const doc = await PDFNet.PDFDoc.createFromURL(docurl);
      doc.initSecurityHandler();
      doc.lock();
      const pagecount = await doc.getPageCount();
      const pdfdraw = await PDFNet.PDFDraw.create(100);
      return { doc, pdfdraw, pagecount };
    } catch (err) {
      console.log(err.stack);
    }
  };

  const renderPage = async (renderData, pageIndex) => {
    try {
      const doc = renderData.doc;
      const pdfdraw = renderData.pdfdraw;

      const currentPage = await doc.getPage(pageIndex);
      const bitmapInfo = await pdfdraw.getBitmap(currentPage, PDFNet.PDFDraw.PixelFormat.e_rgba, false);
      const bitmapWidth = bitmapInfo.width;
      const bitmapHeight = bitmapInfo.height;
      const bitmapArray = new Uint8ClampedArray(bitmapInfo.buf);

      const drawingCanvas = document.createElement('canvas');
      drawingCanvas.width = bitmapWidth;
      drawingCanvas.height = bitmapHeight;

      const ctx = drawingCanvas.getContext('2d');
      const imgData = ctx.createImageData(bitmapWidth, bitmapHeight);
      imgData.data.set(bitmapArray);

      ctx.putImageData(imgData, 0, 0);
      return drawingCanvas;
    } catch (err) {
      console.log(err.stack);
    }
  };

  // use "runWithoutCleanup" to lock the document data and run callback, use "with out cleanup" so data isn't cleared afterwards
  // add your own license key as the second parameter, e.g. PDFNet.runWithoutCleanup(main, 'YOUR_LICENSE_KEY')
  exports.loadDocument = docurl => PDFNet.runWithoutCleanup(async () => initAll(docurl), window.parent.sampleL);

  exports.loadCanvasAsync = (renderData, pageIndex) => PDFNet.runWithoutCleanup(async () => renderPage(renderData, pageIndex));
})(window);
// # sourceURL=DeckJSTest.js
