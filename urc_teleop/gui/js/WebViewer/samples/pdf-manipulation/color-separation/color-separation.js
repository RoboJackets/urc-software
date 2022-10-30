// @link WebViewerInstance: https://www.pdftron.com/api/web/WebViewerInstance.html
// @link UI.openElements: https://www.pdftron.com/api/web/UI.html#openElements__anchor
// @link UI.closeElements: https://www.pdftron.com/api/web/UI.html#closeElements__anchor

// @link DocumentViewer: https://www.pdftron.com/api/web/Core.DocumentViewer.html
// @link DocumentViewer.getToolMode.getMouseLocation: https://www.pdftron.com/api/web/Tools.Tool.html#getMouseLocation__anchor
// @link DocumentViewer.getDisplayModeManager.getDisplayMode: https://www.pdftron.com/api/web/Core.DisplayMode.html
// @link DocumentViewer.getColorSeparationsAtPoint: https://www.pdftron.com/api/web/Core.DocumentViewer.html#getColorSeparationsAtPoint__anchor
// @link DocumentViewer.refreshAll: https://www.pdftron.com/api/web/Core.DocumentViewer.html#refreshAll__anchor
// @link DocumentViewer.updateView: https://www.pdftron.com/api/web/Core.DocumentViewer.html#updateView__anchor

// @link displayMode.windowToPage: https://www.pdftron.com/api/web/Core.DisplayMode.html#windowToPage__anchor

// @link Document: https://www.pdftron.com/api/web/Core.Document.html
// @link Document.enableColorSeparations: https://www.pdftron.com/api/web/Core.Document.html#enableColorSeparations__anchor
// @link Document.enableSeparation: https://www.pdftron.com/api/web/Core.Document.html#enableSeparation__anchor

WebViewer(
  {
    path: '../../../lib',
    fullAPI: true,
    initialDoc: '../../../samples/files/op-blend-test.pdf',
    enableFilePicker: true,
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const { documentViewer } = instance.Core;
  const { openElements, closeElements } = instance.UI;
  const colorsElement = document.getElementById('colors');

  let colorSeparationLoaded = false;
  documentViewer.addEventListener('documentLoaded', () => {
    colorsElement.innerHTML = '';

    const doc = documentViewer.getDocument();
    colorSeparationLoaded = false;
    // Enable color separation
    doc.enableColorSeparations({ checkIfBaseColorsUsed: false });
    // wait till the individual "colors" in the top left corner load first
    openElements(['loadingModal']);

    // Listen to each color in a PDF document
    doc.addEventListener('colorSeparationAdded', color => {
      colorSeparationLoaded = true;
      const input = document.createElement('input');
      input.id = color.name;
      input.type = 'checkbox';
      input.checked = color.enabled;
      input.onchange = e => {
        // show 'loadingModal', hide it in the 'pageComplete' event
        openElements(['loadingModal']);
        // Show/hide a color
        doc.enableSeparation(color.name, e.target.checked);
        // Redraw the canvas
        documentViewer.refreshAll();
        documentViewer.updateView();
      };

      const label = document.createElement('label');
      label.id = `${color.name} label`;
      label.htmlFor = color.name;
      label.style.color = `rgb(${color.rgb.join(',')})`;
      label.innerHTML = color.name;

      const lineBreak = document.createElement('br');

      colorsElement.appendChild(input);
      colorsElement.appendChild(label);
      colorsElement.appendChild(lineBreak);
      closeElements(['loadingModal']);
    });
  });

  documentViewer.addEventListener('mouseMove', nativeE => {
    const mouseLocation = documentViewer.getToolMode().getMouseLocation(nativeE);
    const displayMode = documentViewer.getDisplayModeManager().getDisplayMode();

    const pageNumber = displayMode.getSelectedPages(mouseLocation, mouseLocation).first;
    if (pageNumber !== null) {
      const pageCoordinate = displayMode.windowToPage(mouseLocation, pageNumber);
      if (pageCoordinate) {
        const pageNumber = pageCoordinate.pageNumber;
        const x = pageCoordinate.x;
        const y = pageCoordinate.y;
        const results = documentViewer.getColorSeparationsAtPoint(pageNumber, x, y);
        for (let i = 0; i < results.length; ++i) {
          // Update the text in color panel
          const colorLabelElement = document.getElementById(`${results[i].name} label`);
          if (colorLabelElement) {
            colorLabelElement.innerHTML = `${results[i].name} ${results[i].value}%`;
          }
        }
      }
    }
  });

  documentViewer.addEventListener('pageComplete', () => {
    // wait for the first 'colorSeparationAdded' event before closing the loading modal
    // we don't want to hide the 'loadingModal' for the first 'pageComplete' event for the initial load
    if (colorSeparationLoaded) {
      closeElements(['loadingModal']);
    }
  });
});
