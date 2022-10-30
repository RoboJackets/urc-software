This sample is provided for reference but you can also use it as a basis to add custom pixel-by-pixel comparison in your product using Webviewer. To get started on your own custom pixel by pixel feature, please do the following:

Copy over all files in this folder to your projects EXCEPT for:
- diff.css
- diff.js
- diff-alignment-tool.js
- diff-overlay-slider.js
- nudge-tool.css
- nudge-tool.js
- index.html
- license.txt
- assets folder

The above mentioned files are only specific to this sample.

To get started, please call the initialization function:
```
// note that some of this is pseudo-code
CompareDocumentManager.initialize(
      webviewerInstance.Core,
      files,
      {
        // options
      }
    );
```
`CompareDocumentManager` is the class that handles setup and initialization of the `CompareDocument` object so that WebViewer can display the differences.
Please see `compare-document-manager.js` for more information.

---

To call the API that will handle alignment:

```
const compareDocument = webviewer.Core.getDocument();
compareDocument.updatePageWithAlignment(...)
```

Alignment is where a line exists in a source document and another line exists in a target document.
The line in the source document will scale/translate/rotate itself (this will also cause the source document to transform in the same way) to match the line in the target document.

To call the API that will handle nudging:

```
const compareDocument = webviewer.Core.documentViewer.getDocument();
compareDocument.translate(...)
compareDocument.scale(...)
compareDocument.rotate(...)
```

Please see for `public-apis-for-compare-docs.js` for more information.

---

Please see `diff.js` for sample usages for the code mentioned in this readme.