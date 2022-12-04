//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/Core.PDFNet.PDFNet.html
  // @link PDFDoc: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html
  // @link ContentReplacer: https://www.pdftron.com/api/web/Core.PDFNet.ContentReplacer.html
  // @link Image: https://www.pdftron.com/api/web/Core.PDFNet.Image.html
  // @link Matrix2D: https://www.pdftron.com/api/web/Core.PDFNet.Matrix2D.html
  // @link Page: https://www.pdftron.com/api/web/Core.PDFNet.Page.html

  exports.runContentReplacer = () => {
    const PDFNet = exports.Core.PDFNet;

    const main = async () => {
      try {
        const inputUrl = '../TestFiles/';
        const inputFilename = 'BusinessCardTemplate.pdf';
        const outputFilename = 'BusinessCard.pdf';

        const doc = await PDFNet.PDFDoc.createFromURL(inputUrl + inputFilename);
        doc.initSecurityHandler();
        doc.lock();

        const replacer = await PDFNet.ContentReplacer.create();
        const page = await doc.getPage(1);
        const img = await PDFNet.Image.createFromURL(doc, inputUrl + 'peppers.jpg');

        const region = await page.getMediaBox();
        const replace = await img.getSDFObj();
        await replacer.addImage(region, replace);
        await replacer.addString('NAME', 'John Smith');
        await replacer.addString('QUALIFICATIONS', 'Philosophy Doctor');
        await replacer.addString('JOB_TITLE', 'Software Developer');
        await replacer.addString('ADDRESS_LINE1', '#100 123 Software Rd');
        await replacer.addString('ADDRESS_LINE2', 'Vancouver, BC');
        await replacer.addString('PHONE_OFFICE', '604-730-8989');
        await replacer.addString('PHONE_MOBILE', '604-765-4321');
        await replacer.addString('EMAIL', 'info@pdftron.com');
        await replacer.addString('WEBSITE_URL', 'http://www.pdftron.com');
        await replacer.process(page);

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_remove_unused);
        saveBufferAsPDFDoc(docbuf, outputFilename);

        console.log('Done. Result saved in ' + outputFilename);
      } catch (err) {
        console.log(err);
      }
      try {
        const inputUrl = '../TestFiles/';
        const inputFilename = 'newsletter.pdf';
        const outputFilename = 'ContentReplaced.pdf';

        const doc = await PDFNet.PDFDoc.createFromURL(inputUrl + inputFilename);
        doc.initSecurityHandler();
        doc.lock();

        const replacer = await PDFNet.ContentReplacer.create();
        const page = await doc.getPage(1);
        const region = await page.getMediaBox();
        await replacer.addText(region, 'The quick onyx goblin jumps over the lazy dwarf');
        await replacer.process(page);

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_remove_unused);
        saveBufferAsPDFDoc(docbuf, outputFilename);

        console.log('Done. Result saved in ' + outputFilename);
        console.log('Done.');
      } catch (err) {
        console.log(err);
      }
    };
    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=ContentReplacerTest.js
