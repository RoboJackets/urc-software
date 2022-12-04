(() => {
  const parentDocument = window.parent.document;
  const certSelect = parentDocument.getElementById('certificate-select');
  const certUrlForm = parentDocument.getElementById('certificate-url-form');
  const docSelect = parentDocument.getElementById('document-select');
  const docUrlForm = parentDocument.getElementById('document-url-form');
  const filePicker = parentDocument.getElementById('file-picker');

  window.addEventListener('viewerLoaded', () => {
    const instance = window.instance;
    const { VerificationOptions, openElements, loadDocument } = instance.UI;
    const { documentViewer } = instance.Core;

    const initialCert = 'https://pdftron.s3.amazonaws.com/downloads/pl/waiver.cer';
    VerificationOptions.addTrustedCertificates([initialCert]);

    documentViewer.addEventListener(
      'documentLoaded',
      () => {
        openElements(['signaturePanel']);
      },
      { once: true }
    );

    certSelect.addEventListener('change', e => {
      VerificationOptions.addTrustedCertificates([e.target.value]);
    });

    certUrlForm.addEventListener('submit', e => {
      e.preventDefault();

      certSelect.value = '';

      const certUrl = document.getElementById('certificate-url');
      VerificationOptions.addTrustedCertificates([certUrl.value]);
    });

    docSelect.addEventListener('change', e => {
      loadDocument(e.target.value);
    });

    docUrlForm.addEventListener('submit', e => {
      e.preventDefault();

      docSelect.value = '';

      const docUrl = document.getElementById('document-url');
      loadDocument(docUrl.value);
    });

    filePicker.addEventListener('change', e => {
      const file = e.target.files[0];

      if (!file) {
        return;
      }

      const ext = file.name.slice(file.name.lastIndexOf('.') + 1);

      if (ext === 'cer') {
        certSelect.value = '';
        VerificationOptions.addTrustedCertificates([file]);
      } else if (ext === 'pdf') {
        docSelect.value = '';
        loadDocument(file);
      }
    });
  });
})();
// eslint-disable-next-line spaced-comment
//# sourceURL=config.js
