//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/Core.PDFNet.html
  // @link PDFNet.PDFDoc: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html
  // @link PDFNet.PDFDraw: https://www.pdftron.com/api/web/Core.PDFNet.PDFDraw.html

  exports.runPDFDrawTest = () => {
    const PDFNet = exports.Core.PDFNet;

    const main = async () => {
      console.log('Beginning Test');
      const ret = 0;
      const inputUrl = '../TestFiles/';
      const doc = await PDFNet.PDFDoc.createFromURL(inputUrl + 'newsletter.pdf');
      doc.initSecurityHandler();
      doc.lock();

      console.log('PDFNet and PDF document initialized and locked');

      const pdfdraw = await PDFNet.PDFDraw.create(92);
      const itr = await doc.getPageIterator(1);
      const currPage = await itr.current();
      const pngBuffer = await pdfdraw.exportStream(currPage, 'PNG');
      saveBufferAsPNG(pngBuffer, 'newsletter.png');
      const tifBuffer = await pdfdraw.exportStream(currPage, 'TIFF');
      saveBufferAsPNG(tifBuffer, 'newsletter.tif');

      console.log('Done');
      return ret;
    };

    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=PDFDrawTest.js
