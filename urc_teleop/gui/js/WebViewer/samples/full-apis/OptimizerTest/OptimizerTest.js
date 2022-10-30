//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2019 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// The following sample illustrates how to reduce PDF file size using 'pdftron.PDF.Optimizer'.
// The sample also shows how to simplify and optimize PDF documents for viewing on mobile devices
// and on the Web using 'pdftron.PDF.Flattener'.
//
// @note Both 'Optimizer' and 'Flattener' are separately licensable add-on options to the core PDFNet license.
//
// ----
//
// 'pdftron.PDF.Optimizer' can be used to optimize PDF documents by reducing the file size, removing
// redundant information, and compressing data streams using the latest in image compression technology.
//
// PDF Optimizer can compress and shrink PDF file size with the following operations:
// - Remove duplicated fonts, images, ICC profiles, and any other data stream.
// - Optionally convert high-quality or print-ready PDF files to small, efficient and web-ready PDF.
// - Optionally down-sample large images to a given resolution.
// - Optionally compress or recompress PDF images using JBIG2 and JPEG2000 compression formats.
// - Compress uncompressed streams and remove unused PDF objects.
//
// ----
//
// 'pdftron.PDF.Flattener' can be used to speed-up PDF rendering on mobile devices and on the Web by
// simplifying page content (e.g. flattening complex graphics into images) while maintaining vector text
// whenever possible.
//
// Flattener can also be used to simplify process of writing custom converters from PDF to other formats.
// In this case, Flattener can be used as first step in the conversion pipeline to reduce any PDF to a
// very simple representation (e.g. vector text on top of a background image).
//---------------------------------------------------------------------------------------

(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/Core.PDFNet.html
  // @link PDFNet.PDFDoc: https://www.pdftron.com/api/web/Core.PDFNet.PDFDoc.html
  const PDFNet = exports.Core.PDFNet;

  exports.runOptimizerTest = () => {
    const main = async () => {
      const inputPath = '../TestFiles/';
      const inputFilename = 'newsletter';

      // The first step in every application using PDFNet is to initialize the
      // library and set the path to common PDF resources. The library is usually
      // initialized only once, but calling Initialize() multiple times is also fine.

      //--------------------------------------------------------------------------------
      // Example 1) Simple optimization of a pdf with default settings.
      //
      try {
        const doc = await PDFNet.PDFDoc.createFromURL(inputPath + inputFilename + '.pdf');
        doc.initSecurityHandler();
        await doc.lock();
        await PDFNet.Optimizer.optimize(doc);
        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, inputFilename + '_opt1.pdf');
      } catch (err) {
        console.log(err);
      }

      //--------------------------------------------------------------------------------
      // Example 2) Reduce image quality and use jpeg compression for
      // non monochrome images.
      try {
        const doc = await PDFNet.PDFDoc.createFromURL(inputPath + inputFilename + '.pdf');
        doc.initSecurityHandler();
        await doc.lock();
        const imageSettings = new PDFNet.Optimizer.ImageSettings();

        // low quality jpeg compression
        imageSettings.setCompressionMode(PDFNet.Optimizer.ImageSettings.CompressionMode.e_jpeg);
        imageSettings.setQuality(1);

        // Set the output dpi to be standard screen resolution
        imageSettings.setImageDPI(144, 96);

        // this option will recompress images not compressed with
        // jpeg compression and use the result if the new image
        // is smaller.
        imageSettings.forceRecompression(true);

        // this option is not commonly used since it can
        // potentially lead to larger files.  It should be enabled
        // only if the output compression specified should be applied
        // to every image of a given type regardless of the output image size
        // imageSettings.forceChanges(true);

        const optSettings = new PDFNet.Optimizer.OptimizerSettings();
        optSettings.setColorImageSettings(imageSettings);
        optSettings.setGrayscaleImageSettings(imageSettings);

        // use the same settings for both color and grayscale images
        await PDFNet.Optimizer.optimize(doc, optSettings);

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, inputFilename + '_opt2.pdf');
      } catch (err) {
        console.log(err);
      }

      //--------------------------------------------------------------------------------
      // Example 3) Use monochrome image settings and default settings
      // for color and grayscale images.
      try {
        const doc = await PDFNet.PDFDoc.createFromURL(inputPath + inputFilename + '.pdf');
        doc.initSecurityHandler();
        await doc.lock();

        const monoImageSettings = new PDFNet.Optimizer.MonoImageSettings();

        monoImageSettings.setCompressionMode(PDFNet.Optimizer.MonoImageSettings.CompressionMode.e_jbig2);
        monoImageSettings.forceRecompression(true);

        const optSettings = new PDFNet.Optimizer.OptimizerSettings();

        optSettings.setMonoImageSettings(monoImageSettings);

        await PDFNet.Optimizer.optimize(doc, optSettings);

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, inputFilename + '_opt3.pdf');
      } catch (err) {
        console.log(err);
      }

      // ----------------------------------------------------------------------
      // Example 4) Use Flattener to simplify content in this document
      // using default settings
      try {
        const doc = await PDFNet.PDFDoc.createFromURL(inputPath + 'TigerText.pdf');
        doc.initSecurityHandler();
        await doc.lock();

        const fl = await PDFNet.Flattener.create();

        // The following lines can increase the resolution of background
        // images.
        // fl.setDPI(300);
        // fl.setMaximumImagePixels(5000000);

        // This line can be used to output Flate compressed background
        // images rather than DCTDecode compressed images which is the default
        // fl.setPreferJPG(false);

        // In order to adjust thresholds for when text is Flattened
        // the following function can be used.
        // fl.setThreshold(PDFNet.Flattener.Threshold.e_keep_most);

        // We use e_fast option here since it is usually preferable
        // to avoid Flattening simple pages in terms of size and
        // rendering speed. If the desire is to simplify the
        // document for processing such that it contains only text and
        // a background image e_simple should be used instead.
        await fl.process(doc, PDFNet.Flattener.Mode.e_fast);

        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
        saveBufferAsPDFDoc(docbuf, 'TigerText_flatten.pdf');
      } catch (err) {
        console.log(err);
      }
    };

    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
  exports.runOptimizerTest();
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=OptimizerTest.js
