//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------
(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/Core.PDFNet.PDFNet.html
  // @link PDFNet.runWithCleanup: https://www.pdftron.com/api/web/Core.PDFNet.html#.runWithCleanup__anchor

  // @link PDFDoc: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html
  // @link PDFDoc.createFromURL: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#.createFromURL__anchor
  // @link PDFDoc.createIndirectStreamFromFilter: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#createIndirectStreamFromFilter__anchor
  // @link PDFDoc.initSecurityHandler: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#initSecurityHandler__anchor
  // @link PDFDoc.lock: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#lock__anchor
  // @link PDFDoc.getTrailer: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#getTrailer__anchor
  // @link PDFDoc.getSecurityHandler: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#getSecurityHandler__anchor
  // @link PDFDoc.saveMemoryBuffer: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#saveMemoryBuffer__anchor
  // @link PDFDoc.removeSecurity: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html#removeSecurity__anchor

  // @link Filter: https://www.pdftron.com/api/web/Core.PDFNet.Filter.html
  // @link Filter.createURLFilter: https://www.pdftron.com/api/web/Core.PDFNet.Filter.html#.createURLFilter__anchor
  // @link Filter.createFlateEncode: https://www.pdftron.com/api/web/Core.PDFNet.Filter.html#.createFlateEncode__anchor

  // @link FilterReader: https://www.pdftron.com/api/web/Core.PDFNet.FilterReader.html
  // @link FilterReader.create: https://www.pdftron.com/api/web/Core.PDFNet.FilterReader.html#.create__anchor

  // @link SecurityHandler: https://www.pdftron.com/api/web/Core.PDFNet.SecurityHandler.html
  // @link SecurityHandler.getPermission: https://www.pdftron.com/api/web/Core.PDFNet.SecurityHandler.html#getPermission__anchor

  // @link Obj: https://www.pdftron.com/api/web/Core.PDFNet.Obj.html
  // @link Obj.get: https://www.pdftron.com/api/web/Core.PDFNet.Obj.html#get__anchor
  // @link Obj.value: https://www.pdftron.com/api/web/Core.PDFNet.Obj.html#value__anchor
  // @link Obj.getAt: https://www.pdftron.com/api/web/Core.PDFNet.Obj.html#getAt__anchor

  exports.runEncTest = () => {
    const PDFNet = exports.Core.PDFNet;

    const main = async () => {
      console.log('Beginning Test');
      let ret = 0;
      // Relative path to the folder containing test files.
      const inputUrl = '../TestFiles/';
      let doc = null;
      // Example 1:
      // secure a PDF document with password protection and adjust permissions
      try {
        console.log('Running Sample 1');
        doc = await PDFNet.PDFDoc.createFromURL(inputUrl + 'fish.pdf');
        doc.initSecurityHandler();
        doc.lock();
        console.log('PDFNet and PDF document initialized and locked');

        const performOperation = true; // optional parameter

        // Perform some operation on the document. In this case we use low level SDF API
        // to replace the content stream of the first page with contents of file 'my_stream.txt'
        // Results in fish.pdf becoming a pair of feathers.
        if (performOperation) {
          console.log('Replacing the content stream, use Flate compression...');
          // Get the page dictionary using the following path: trailer/Root/Pages/Kids/0
          const pageTrailer = await doc.getTrailer();
          const pageRoot = await pageTrailer.get('Root');
          const pageRootValue = await pageRoot.value();
          const pages = await pageRootValue.get('Pages');
          const pagesVal = await pages.value();
          const kids = await pagesVal.get('Kids');
          const kidsVal = await kids.value();
          const pageDict = await kidsVal.getAt(0);

          const embedFile = await PDFNet.Filter.createURLFilter(inputUrl + 'my_stream.txt');
          const mystm = await PDFNet.FilterReader.create(embedFile);

          const emptyFilter = new PDFNet.Filter('0');
          const flateEncode = await PDFNet.Filter.createFlateEncode(emptyFilter);

          const indStream = await doc.createIndirectStreamFromFilter(mystm, flateEncode);
          await pageDict.put('Contents', indStream);
        }

        // Encrypt the document
        // Apply a new security handler with given security settings.
        // In order to open saved PDF you will need a user password 'test'.
        const newHandler = await PDFNet.SecurityHandler.createDefault();

        // Set a new password required to open a document
        newHandler.changeUserPasswordUString('test');
        console.log("Setting password to 'test'");

        // Set Permissions
        newHandler.setPermission(PDFNet.SecurityHandler.Permission.e_print, false);
        newHandler.setPermission(PDFNet.SecurityHandler.Permission.e_extract_content, true);

        // Note: document takes the ownership of newHandler.
        doc.setSecurityHandler(newHandler);

        // Save the changes
        console.log('Saving modified file...');

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, 'secured.pdf');
      } catch (err) {
        console.log(err);
        console.log(err.stack);
        ret = 1;
      }

      // Example 2:
      // Opens an encrypted PDF document and removes its security.
      try {
        console.log('Running Sample 2');
        const securedDoc = doc;

        if (!(await securedDoc.initSecurityHandler())) {
          let success = false;
          console.log("The password has been set to : 'test'");
          const passwordsToTry = ['password', 'testy', 'test'];

          for (let count = 0; count < passwordsToTry.length; count++) {
            const candidate = passwordsToTry[count];
            console.log("Trying password candidate: '" + candidate + "'");
            if (await securedDoc.initStdSecurityHandlerUString(candidate)) {
              success = true;
              console.log('The password is correct');
              break;
            } else {
              console.log('The password is incorrect.');
            }
          }
          if (!success) {
            console.log('Document authentication error...');
            ret = 1;
            return ret;
          }
        }
        securedDoc.lock();

        console.log('PDF document initialized and locked');
        const hdlr = await securedDoc.getSecurityHandler();

        console.log('Document Open Password: ' + (await hdlr.isUserPasswordRequired()));
        console.log('Permissions Password: ' + (await hdlr.isMasterPasswordRequired()));
        console.log('Permissions: ');
        console.log("\tHas 'owner' permissions: " + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_owner)));

        console.log('\tOpen and decrypt the document: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_doc_open)));
        console.log('\tAllow content extraction: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_extract_content)));
        console.log('\tAllow full document editing: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_doc_modify)));
        console.log('\tAllow printing: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_print)));
        console.log('\tAllow high resolution printing: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_print_high)));
        console.log('\tAllow annotation editing: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_mod_annot)));
        console.log('\tAllow form fill: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_fill_forms)));
        console.log('\tAllow content extraction for accessibility: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_access_support)));
        console.log('\tAllow document assembly: ' + (await hdlr.getPermission(PDFNet.SecurityHandler.Permission.e_assemble_doc)));

        // remove all security on the document
        securedDoc.removeSecurity();

        const docbuf = await securedDoc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, 'not_secured.pdf');
        console.log('done');
      } catch (err) {
        console.log(err.stack);
        ret = 1;
      }
      return ret;
    };

    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=EncTest.js
