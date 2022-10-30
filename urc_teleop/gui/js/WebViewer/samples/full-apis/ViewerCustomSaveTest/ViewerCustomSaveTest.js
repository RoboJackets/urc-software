(exports => {
  const PDFNet = exports.Core.PDFNet;
  const mergeAndSave = (doc, xfdf) => {
    const main = async () => {
      // Import XFDF into FDF, then merge data from FDF into PDF
      // Annotations
      const fdfDoc = await PDFNet.FDFDoc.createFromXFDF(xfdf);

      const pitr = await doc.getPageIterator();
      let page;
      let annotObj;
      /* eslint no-await-in-loop: 0 */
      for (; await pitr.hasNext(); pitr.next()) {
        try {
          page = await pitr.current();
          for (let i = await page.getNumAnnots(); i > 0; ) {
            annotObj = await page.getAnnot(--i);
            switch (await annotObj.getType()) {
              case PDFNet.Annot.Type.e_Widget:
              case PDFNet.Annot.Type.e_Link:
              case PDFNet.Annot.Type.e_Sound:
              case PDFNet.Annot.Type.e_Movie:
              case PDFNet.Annot.Type.e_FileAttachment:
                // these are not supported for import from webviewer
                break;
              default:
                page.annotRemoveByIndex(i);
                break;
            }
          }
        } catch (e) {
          console.log('Error Removing Annotations: ' + e);
          (await page.getSDFObj()).erase('Annots');
        }
      }

      await doc.fdfMerge(fdfDoc);

      // run any custom logic here
      await doc.flattenAnnotations();

      const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_linearized);
      return docbuf;
    };
    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    return PDFNet.runWithCleanup(main);
  };

  const customDownload = options => {
    const documentViewer = instance.Core.documentViewer;
    const am = documentViewer.getAnnotationManager();
    const annotationsToRemove = am.getAnnotationsList();
    const currentDocument = documentViewer.getDocument();
    return PDFNet.initialize()
      .then(() => currentDocument.getPDFDoc())
      .then(pdfDoc => mergeAndSave(pdfDoc, options.xfdfString))
      .then(data => {
        // since we are flattening annotations we should remove the existing annotations in webviewer
        // and rerender so that the file displays correctly

        am.deleteAnnotations(annotationsToRemove);
        // clear the cache
        documentViewer.refreshAll();
        // update viewer with new document
        documentViewer.updateView();
        // Annotations may contain text so we need to regenerate
        // our text representation
        documentViewer.getDocument().refreshTextData();
        return data;
      });
  };

  window.addEventListener('documentLoaded', () => {
    const doc = instance.Core.documentViewer.getDocument();
    doc.getFileData = customDownload;
  });
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=config.js
