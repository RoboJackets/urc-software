//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/Core.PDFNet.PDFNet.html
  // @link PDFDoc: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html
  // @link ElementReader: https://www.pdftron.com/api/web/Core.PDFNet.ElementReader.html

  exports.runElementReaderTest = () => {
    const PDFNet = exports.Core.PDFNet;

    const ProcessElements = async reader => {
      // Read page contents
      for (let element = await reader.next(); element !== null; element = await reader.next()) {
        const temp = await element.getType();
        switch (temp) {
          case PDFNet.Element.Type.e_path: // Process path data...
            {
              const data = await element.getPathData();
              /* eslint-disable no-unused-vars */
              const operators = data.operators;
              const points = data.points;
              /* eslint-enable no-unused-vars */
            }
            break;
          case PDFNet.Element.Type.e_text: // Process text strings...
            {
              const data = await element.getTextString();
              console.log(data);
            }
            break;
          case PDFNet.Element.Type.e_form: // Process form XObjects
            reader.formBegin();
            await ProcessElements(reader);
            reader.end();
            break;
          default:
        }
      }
    };

    const main = async () => {
      console.log('-------------------------------------------------');
      console.log('Sample 1 - Extract text data from all pages in the document.');
      console.log('Opening the input pdf...');
      const ret = 0;

      // Relative path to the folder containing test files.
      const inputUrl = '../TestFiles/';

      const doc = await PDFNet.PDFDoc.createFromURL(inputUrl + 'newsletter.pdf'); // await if there is ret that we care about.
      doc.initSecurityHandler();
      doc.lock();

      // eslint-disable-next-line no-unused-vars
      const pgnum = await doc.getPageCount();
      const pageReader = await PDFNet.ElementReader.create();
      const itr = await doc.getPageIterator(1);

      // Read every page
      for (itr; await itr.hasNext(); itr.next()) {
        const curritr = await itr.current();
        pageReader.beginOnPage(curritr);
        await ProcessElements(pageReader);
        pageReader.end();
      }

      console.log('Done.');
      return ret;
    };

    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=ElementReaderTest.js
