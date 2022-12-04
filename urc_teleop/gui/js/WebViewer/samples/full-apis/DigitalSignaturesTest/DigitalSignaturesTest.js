//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2020 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

(exports => {
  // @link PDFNet: https://www.pdftron.com/api/web/PDFNet.PDFNet.html
  // @link PDFDoc: https://www.pdftron.com/api/web/PDFNet.PDFDoc.html
  // @link ElementBuilder: https://www.pdftron.com/api/web/PDFNet.ElementBuilder.html
  // @link ElementWriter: https://www.pdftron.com/api/web/PDFNet.ElementWriter.html
  // @link Image: https://www.pdftron.com/api/web/PDFNet.Image.html
  // @link Page: https://www.pdftron.com/api/web/PDFNet.Page.html
  // @link WidgetAnnot: https://www.pdftron.com/api/web/PDFNet.WidgetAnnot.html
  // @link Obj: https://www.pdftron.com/api/web/PDFNet.Obj.html
  // @link PDFNet.Field: https://www.pdftron.com/api/web/PDFNet.Field.html

  exports.runDigitalSignaturesTest = () => {
    const PDFNet = exports.Core.PDFNet;

    const input_path = '../TestFiles/';

    const VerifySimple = async (in_docpath, in_public_key_file_path) => {
      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();
      console.log('==========');
      const opts = await PDFNet.VerificationOptions.create(PDFNet.VerificationOptions.SecurityLevel.e_compatibility_and_archiving);

      // Add trust root to store of trusted certificates contained in VerificationOptions.
      await opts.addTrustedCertificateFromURL(
        in_public_key_file_path,
        {},
        PDFNet.VerificationOptions.CertificateTrustFlag.e_default_trust + PDFNet.VerificationOptions.CertificateTrustFlag.e_certification_trust
      );

      const result = await doc.verifySignedDigitalSignatures(opts);
      switch (result) {
        case PDFNet.PDFDoc.SignaturesVerificationStatus.e_unsigned:
          console.log('Document has no signed signature fields.');
          return false;
        /* e_failure == bad doc status, digest status, or permissions status
        (i.e. does not include trust issues, because those are flaky due to being network/config-related) */
        case PDFNet.PDFDoc.SignaturesVerificationStatus.e_failure:
          console.log('Hard failure in verification on at least one signature.');
          return false;
        case PDFNet.PDFDoc.SignaturesVerificationStatus.e_untrusted:
          console.log('Could not verify trust for at least one signature.');
          return false;
        case PDFNet.PDFDoc.SignaturesVerificationStatus.e_unsupported:
          /* If necessary, call GetUnsupportedFeatures on VerificationResult to check which
          unsupported features were encountered (requires verification using 'detailed' APIs) */
          console.log('At least one signature contains unsupported features.');
          return false;
        // unsigned sigs skipped; parts of document may be unsigned (check GetByteRanges on signed sigs to find out)
        case PDFNet.PDFDoc.SignaturesVerificationStatus.e_verified:
          console.log('All signed signatures in document verified.');
          return true;
      }

      return false;
    };

    const VerifyAllAndPrint = async (in_docpath, in_public_key_file_path) => {
      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();
      console.log('==========');
      const opts = await PDFNet.VerificationOptions.create(PDFNet.VerificationOptions.SecurityLevel.e_compatibility_and_archiving);

      // Add trust root to store of trusted certificates contained in VerificationOptions.
      // Use trust level corresponding to an identity trusted even for certification signatures.
      await opts.addTrustedCertificateFromURL(
        in_public_key_file_path,
        {},
        PDFNet.VerificationOptions.CertificateTrustFlag.e_default_trust + PDFNet.VerificationOptions.CertificateTrustFlag.e_certification_trust
      );

      // Iterate over the signatures and verify all of them.
      const digsig_fitr = await doc.getDigitalSignatureFieldIteratorBegin();
      let verification_status = true;
      for (; await digsig_fitr.hasNext(); await digsig_fitr.next()) {
        const curr = await digsig_fitr.current();
        const result = await curr.verify(opts);
        if (await result.getVerificationStatus()) {
          console.log('Signature verified, objnum: ' + (await (await curr.getSDFObj()).getObjNum()));
        } else {
          console.log('Signature verification failed, objnum: ' + (await (await curr.getSDFObj()).getObjNum()));
          verification_status = false;
        }

        switch (await result.getDigestAlgorithm()) {
          case PDFNet.DigestAlgorithm.Type.e_SHA1:
            console.log('Digest algorithm: SHA-1');
            break;
          case PDFNet.DigestAlgorithm.Type.e_SHA256:
            console.log('Digest algorithm: SHA-256');
            break;
          case PDFNet.DigestAlgorithm.Type.e_SHA384:
            console.log('Digest algorithm: SHA-384');
            break;
          case PDFNet.DigestAlgorithm.Type.e_SHA512:
            console.log('Digest algorithm: SHA-512');
            break;
          case PDFNet.DigestAlgorithm.Type.e_RIPEMD160:
            console.log('Digest algorithm: RIPEMD-160');
            break;
          case PDFNet.DigestAlgorithm.Type.e_unknown_digest_algorithm:
            console.log('Digest algorithm: unknown');
            break;
        }

        console.log(
          'Detailed verification result: \n\t' +
            (await result.getDocumentStatusAsString()) +
            '\n\t' +
            (await result.getDigestStatusAsString()) +
            '\n\t' +
            (await result.getTrustStatusAsString()) +
            '\n\t' +
            (await result.getPermissionsStatusAsString())
        );

        const changes = await result.getDisallowedChanges();
        for (let i = 0; i < changes.length; ++i) {
          const change = changes[i];
          console.log('\tDisallowed change: ' + (await change.getTypeAsString()) + ', objnum: ' + (await change.getObjNum()));
        }

        // Get and print all the detailed trust-related results, if they are available.
        if (await result.hasTrustVerificationResult()) {
          const trust_verification_result = await result.getTrustVerificationResult();
          console.log((await trust_verification_result.wasSuccessful()) ? 'Trust verified.' : 'Trust not verifiable.');
          console.log(await trust_verification_result.getResultString());

          const tmp_time_t = await trust_verification_result.getTimeOfTrustVerification();
          switch (await trust_verification_result.getTimeOfTrustVerificationEnum()) {
            case PDFNet.VerificationOptions.TimeMode.e_current:
              console.log('Trust verification attempted with respect to current time (as epoch time):' + tmp_time_t);
              break;
            case PDFNet.VerificationOptions.TimeMode.e_signing:
              console.log('Trust verification attempted with respect to signing time (as epoch time): ' + tmp_time_t);
              break;
            case PDFNet.VerificationOptions.TimeMode.e_timestamp:
              console.log('Trust verification attempted with respect to secure embedded timestamp (as epoch time): ' + tmp_time_t);
              break;
          }

          const cert_path = await trust_verification_result.getCertPath();
          if (cert_path.length === 0) {
            console.log('Could not print certificate path.');
          } else {
            console.log('Certificate path:');
            for (let i = 0; i < cert_path.length; i++) {
              console.log('\tCertificate:');
              const full_cert = cert_path[i];
              console.log('\t\tIssuer names:');
              const issuer_dn = await (await full_cert.getIssuerField()).getAllAttributesAndValues();
              for (let j = 0; j < issuer_dn.length; j++) {
                console.log('\t\t\t' + (await issuer_dn[j].getStringValue()));
              }
              console.log('\t\tSubject names:');
              const subject_dn = await (await full_cert.getSubjectField()).getAllAttributesAndValues();
              for (let j = 0; j < subject_dn.length; j++) {
                console.log('\t\t\t' + (await subject_dn[j].getStringValue()));
              }
              console.log('\t\tExtensions:');
              const extension_dn = await full_cert.getExtensions();
              for (let j = 0; j < extension_dn.length; j++) {
                console.log('\t\t\t' + (await extension_dn[j].toString()));
              }
            }
          }
        } else {
          console.log('No detailed trust verification result available.');
        }

        console.log('==========');
      }

      return verification_status;
    };

    const CertifyPDF = async (in_docpath, in_cert_field_name, in_private_key_file_path, in_keyfile_password, in_appearance_image_path, in_outpath) => {
      console.log('================================================================================');
      console.log('Certifying PDF document');

      // Open existing PDF.
      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();

      console.log('PDFDoc has ' + ((await doc.hasSignatures()) ? 'signatures' : 'no signatures'));

      const page1 = await doc.getPage(1);

      // Create a text field that we can lock using the field permissions feature.
      const annot1 = await PDFNet.TextWidget.create(doc, new PDFNet.Rect(50, 550, 350, 600), 'asdf_test_field');
      await page1.annotPushBack(annot1);

      /* Create a new signature form field in the PDFDoc. The name argument is optional;
      leaving it empty causes it to be auto-generated. However, you may need the name for later.
      Acrobat doesn't show digsigfield in side panel if it's without a widget. Using a
      Rect with 0 width and 0 height, or setting the NoPrint/Invisible flags makes it invisible. */
      const certification_sig_field = await doc.createDigitalSignatureField(in_cert_field_name);
      const widgetAnnot = await PDFNet.SignatureWidget.createWithDigitalSignatureField(doc, new PDFNet.Rect(0, 100, 200, 150), certification_sig_field);
      await page1.annotPushBack(widgetAnnot);

      // (OPTIONAL) Add an appearance to the signature field.
      const img = await PDFNet.Image.createFromURL(doc, in_appearance_image_path);
      await widgetAnnot.createSignatureAppearance(img);

      // Prepare the document locking permission level. It will be applied upon document certification.
      console.log('Adding document permissions.');
      await certification_sig_field.setDocumentPermissions(PDFNet.DigitalSignatureField.DocumentPermissions.e_annotating_formfilling_signing_allowed);

      // Prepare to lock the text field that we created earlier.
      console.log('Adding field permissions.');
      const fields_to_lock = ['asdf_test_field'];
      await certification_sig_field.setFieldPermissions(PDFNet.DigitalSignatureField.FieldPermissions.e_include, fields_to_lock);

      await certification_sig_field.certifyOnNextSaveFromURL(in_private_key_file_path, in_keyfile_password);

      // (OPTIONAL) Add more information to the signature dictionary.
      await certification_sig_field.setLocation('Vancouver, BC');
      await certification_sig_field.setReason('Document certification.');
      await certification_sig_field.setContactInfo('www.pdftron.com');

      // Save the PDFDoc. Once the method below is called, PDFNet will also sign the document using the information provided.
      const docbuf = await doc.saveMemoryBuffer(0);
      saveBufferAsPDFDoc(docbuf, in_outpath);

      console.log('================================================================================');

      return docbuf;
    };

    const SignPDF = async (in_docpath, in_approval_field_name, in_private_key_file_path, in_keyfile_password, in_appearance_img_path, in_outpath) => {
      console.log('================================================================================');
      console.log('Signing PDF document');

      // Open an existing PDF
      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();

      // Retrieve the unsigned approval signature field.
      const found_approval_field = await doc.getField(in_approval_field_name);
      const found_approval_signature_digsig_field = await PDFNet.DigitalSignatureField.createFromField(found_approval_field);

      // (OPTIONAL) Add an appearance to the signature field.
      const img = await PDFNet.Image.createFromURL(doc, in_appearance_img_path);
      const found_approval_signature_widget = await PDFNet.SignatureWidget.createFromObj(await found_approval_field.getSDFObj());
      await found_approval_signature_widget.createSignatureAppearance(img);

      // Prepare the signature and signature handler for signing.
      await found_approval_signature_digsig_field.signOnNextSaveFromURL(in_private_key_file_path, in_keyfile_password);

      // The actual approval signing will be done during the following incremental save operation.
      const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_incremental);
      saveBufferAsPDFDoc(docbuf, in_outpath);

      console.log('================================================================================');

      return docbuf;
    };

    const ClearSignature = async (in_docpath, in_digsig_field_name, in_outpath) => {
      console.log('================================================================================');
      console.log('Clearing certification signature');

      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();

      const digsig = await PDFNet.DigitalSignatureField.createFromField(await doc.getField(in_digsig_field_name));

      console.log('Clearing signature: ' + in_digsig_field_name);
      await digsig.clearSignature();

      if (!(await digsig.hasCryptographicSignature())) {
        console.log('Cryptographic signature cleared properly.');
      }

      // Save incrementally so as to not invalidate other signatures from previous saves.
      const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_incremental);
      saveBufferAsPDFDoc(docbuf, in_outpath);

      console.log('================================================================================');

      return docbuf;
    };

    const PrintSignaturesInfo = async in_docbuffer => {
      console.log('================================================================================');
      console.log('Reading and printing digital signature information');

      const doc = await PDFNet.PDFDoc.createFromBuffer(in_docbuffer);
      doc.initSecurityHandler();
      doc.lock();
      if (!(await doc.hasSignatures())) {
        console.log('Doc has no signatures.');
        console.log('================================================================================');
        return;
      }
      console.log('Doc has signatures.');

      for (const fitr = await doc.getFieldIteratorBegin(); await fitr.hasNext(); await fitr.next()) {
        const field = await fitr.current();
        // eslint-disable-next-line no-unused-expressions
        (await field.isLockedByDigitalSignature()) ? console.log('==========\nField locked by a digital signature') : console.log('==========\nField not locked by a digital signature');

        console.log('Field name: ' + (await field.getName()));
        console.log('==========');
      }

      console.log('====================\nNow iterating over digital signatures only.\n====================');

      const digsig_fitr = await doc.getDigitalSignatureFieldIteratorBegin();
      for (; await digsig_fitr.hasNext(); await digsig_fitr.next()) {
        console.log('==========');
        const digsigfield = await digsig_fitr.current();
        console.log('Field name of digital signature: ' + (await (await PDFNet.Field.create(await digsigfield.getSDFObj())).getName()));

        if (!(await digsigfield.hasCryptographicSignature())) {
          console.log(
            'Either digital signature field lacks a digital signature dictionary, ' +
              'or digital signature dictionary lacks a cryptographic Contents entry. ' +
              'Digital signature field is not presently considered signed.\n' +
              '=========='
          );
          continue;
        }

        const cert_count = await digsigfield.getCertCount();
        console.log('Cert count: ' + cert_count);
        for (let i = 0; i < cert_count; i++) {
          const cert = await digsigfield.getCert(i);
          console.log('Cert #' + i + ' size: ' + cert.byteLength);
        }

        const subfilter = await digsigfield.getSubFilter();

        console.log('Subfilter type: ' + subfilter);

        if (subfilter !== PDFNet.DigitalSignatureField.SubFilterType.e_ETSI_RFC3161) {
          console.log("Signature's signer: " + (await digsigfield.getSignatureName()));

          const signing_time = await digsigfield.getSigningTime();
          if (await signing_time.isValid()) {
            console.log('Signing time is valid.');
          }

          console.log('Location: ' + (await digsigfield.getLocation()));
          console.log('Reason: ' + (await digsigfield.getReason()));
          console.log('Contact info: ' + (await digsigfield.getContactInfo()));
        } else {
          console.log('SubFilter == e_ETSI_RFC3161 (DocTimeStamp; no signing info)');
        }

        console.log((await digsigfield.hasVisibleAppearance()) ? 'Visible' : 'Not visible');

        const digsig_doc_perms = await digsigfield.getDocumentPermissions();
        const locked_fields = await digsigfield.getLockedFields();
        for (let i = 0; i < locked_fields.length; i++) {
          console.log('This digital signature locks a field named: ' + locked_fields[i]);
        }

        switch (digsig_doc_perms) {
          case PDFNet.DigitalSignatureField.DocumentPermissions.e_no_changes_allowed:
            console.log('No changes to the document can be made without invalidating this digital signature.');
            break;
          case PDFNet.DigitalSignatureField.DocumentPermissions.e_formfilling_signing_allowed:
            console.log('Page template instantiation, form filling, and signing digital signatures are allowed without invalidating this digital signature.');
            break;
          case PDFNet.DigitalSignatureField.DocumentPermissions.e_annotating_formfilling_signing_allowed:
            console.log('Annotating, page template instantiation, form filling, and signing digital signatures are allowed without invalidating this digital signature.');
            break;
          case PDFNet.DigitalSignatureField.DocumentPermissions.e_unrestricted:
            console.log('Document not restricted by this digital signature.');
            break;
        }
        console.log('==========');
      }

      console.log('================================================================================');
    };

    // eslint-disable-next-line no-unused-vars
    const TimestampAndEnableLTV = async (in_docpath, in_trusted_cert_path, in_appearance_img_path, in_outpath) => {
      const doc = await PDFNet.PDFDoc.createFromURL(in_docpath);
      doc.initSecurityHandler();
      doc.lock();
      const doctimestamp_signature_field = await doc.createDigitalSignatureField();
      const tst_config = await PDFNet.TimestampingConfiguration.createFromURL('http://rfc3161timestamp.globalsign.com/advanced');
      const opts = await PDFNet.VerificationOptions.create(PDFNet.VerificationOptions.SecurityLevel.e_compatibility_and_archiving);
      /* It is necessary to add to the VerificationOptions a trusted root certificate corresponding to
      the chain used by the timestamp authority to sign the timestamp token, in order for the timestamp
      response to be verifiable during DocTimeStamp signing. It is also necessary in the context of this
      function to do this for the later LTV section, because one needs to be able to verify the DocTimeStamp
      in order to enable LTV for it, and we re-use the VerificationOptions opts object in that part. */
      await opts.addTrustedCertificateFromURL(in_trusted_cert_path);
      /* By default, we only check online for revocation of certificates using the newer and lighter
      OCSP protocol as opposed to CRL, due to lower resource usage and greater reliability. However,
      it may be necessary to enable online CRL revocation checking in order to verify some timestamps
      (i.e. those that do not have an OCSP responder URL for all non-trusted certificates). */
      await opts.enableOnlineCRLRevocationChecking(true);

      const widgetAnnot = await PDFNet.SignatureWidget.createWithDigitalSignatureField(doc, new PDFNet.Rect(0, 100, 200, 150), doctimestamp_signature_field);
      await (await doc.getPage(1)).annotPushBack(widgetAnnot);

      // (OPTIONAL) Add an appearance to the signature field.
      const img = await PDFNet.Image.createFromURL(doc, in_appearance_img_path);
      await widgetAnnot.createSignatureAppearance(img);

      console.log('Testing timestamping configuration.');
      const config_result = await tst_config.testConfiguration(opts);
      if (await config_result.getStatus()) {
        console.log('Success: timestamping configuration usable. Attempting to timestamp.');
      } else {
        // Print details of timestamping failure.
        console.log(await config_result.getString());
        if (await config_result.hasResponseVerificationResult()) {
          const tst_result = await config_result.getResponseVerificationResult();
          console.log('CMS digest status: ' + (await tst_result.getCMSDigestStatusAsString()));
          console.log('Message digest status: ' + (await tst_result.getMessageImprintDigestStatusAsString()));
          console.log('Trust status: ' + (await tst_result.getTrustStatusAsString()));
        }
        return false;
      }

      await doctimestamp_signature_field.timestampOnNextSave(tst_config, opts);

      // Save/signing throws if timestamping fails.
      let docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_incremental);
      saveBufferAsPDFDoc(docbuf, in_outpath);

      console.log('Timestamping successful. Adding LTV information for DocTimeStamp signature.');

      // Add LTV information for timestamp signature to document.
      const timestamp_verification_result = await doctimestamp_signature_field.verify(opts);
      if (!(await doctimestamp_signature_field.enableLTVOfflineVerification(timestamp_verification_result))) {
        console.log('Could not enable LTV for DocTimeStamp.');
        return false;
      }
      docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_incremental);
      saveBufferAsPDFDoc(docbuf, in_outpath);
      console.log('Added LTV information for DocTimeStamp signature successfully.');

      return true;
    };

    const main = async () => {
      let ret = 0;

      // ////////////////// TEST 0:
      /* Create an approval signature field that we can sign after certifying.
      (Must be done before calling CertifyOnNextSave/SignOnNextSave/WithCustomHandler.) */
      try {
        const doc = await PDFNet.PDFDoc.createFromURL(input_path + 'waiver.pdf');
        doc.initSecurityHandler();
        doc.lock();
        const approval_signature_field = await doc.createDigitalSignatureField('PDFTronApprovalSig');
        const widgetAnnotApproval = await PDFNet.SignatureWidget.createWithDigitalSignatureField(doc, new PDFNet.Rect(300, 300, 500, 200), approval_signature_field);
        const page1 = await doc.getPage(1);
        await page1.annotPushBack(widgetAnnotApproval);
        const docbuf = await doc.saveMemoryBuffer(PDFNet.SDFDoc.SaveOptions.e_remove_unused);
        saveBufferAsPDFDoc(docbuf, 'waiver_withApprovalField_output.pdf');
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // ////////////////// TEST 1: certify a PDF.
      try {
        const docbuf = await CertifyPDF(
          input_path + 'waiver_withApprovalField.pdf',
          'PDFTronCertificationSig',
          input_path + 'pdftron.pfx',
          'password',
          input_path + 'pdftron.bmp',
          'waiver_withApprovalField_certified_output.pdf'
        );
        await PrintSignaturesInfo(docbuf);
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // ////////////////// TEST 2: sign a PDF with a certification and an unsigned signature field in it.
      try {
        const docbuf = await SignPDF(
          input_path + 'waiver_withApprovalField_certified.pdf',
          'PDFTronApprovalSig',
          input_path + 'pdftron.pfx',
          'password',
          input_path + 'signature.jpg',
          'waiver_withApprovalField_certified_approved_output.pdf'
        );
        await PrintSignaturesInfo(docbuf);
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // ////////////////// TEST 3: Clear a certification from a document that is certified and has an approval signature.
      try {
        const docbuf = await ClearSignature(
          input_path + 'waiver_withApprovalField_certified_approved.pdf',
          'PDFTronCertificationSig',
          'waiver_withApprovalField_certified_approved_certcleared_output.pdf'
        );
        await PrintSignaturesInfo(docbuf);
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // ////////////////// TEST 4: Verify a document's digital signatures.
      // EXPERIMENTAL. Digital signature verification is undergoing active development, but currently does not support a number of features. If we are missing a feature that is important to you, or if you have files that do not act as expected, please contact us using one of the following forms: https://www.pdftron.com/form/trial-support/ or https://www.pdftron.com/form/request/
      try {
        if (!(await VerifyAllAndPrint(input_path + 'waiver_withApprovalField_certified_approved.pdf', input_path + 'pdftron.cer'))) {
          ret = 1;
        }
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // ////////////////// TEST 5: Verify a document's digital signatures in a simple fashion using the document API.
      try {
        if (!(await VerifySimple(input_path + 'waiver_withApprovalField_certified_approved.pdf', input_path + 'pdftron.cer'))) {
          ret = 1;
        }
      } catch (err) {
        console.log(err);
        ret = 1;
      }

      // //////////////////// TEST 6: Timestamp a document, then add Long Term Validation (LTV) information for the DocTimeStamp.
      // try {
      //   if (!(await TimestampAndEnableLTV(input_path + 'waiver.pdf',
      //     input_path + 'GlobalSignRootForTST.cer',
      //     input_path + 'signature.jpg',
      //     'waiver_DocTimeStamp_LTV.pdf'))) {
      //     ret = 1;
      //   }
      // } catch (err) {
      //   console.log(err);
      //   ret = 1;
      // }

      // ////////////////// End of tests. ////////////////////
      if (!ret) {
        console.log('Tests successful.\n==========');
      } else {
        console.log('Tests FAILED!!!\n==========');
      }
    };

    // add your own license key as the second parameter, e.g. PDFNet.runWithCleanup(main, 'YOUR_LICENSE_KEY')
    PDFNet.runWithCleanup(main);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=DigitalSignaturesTest.js
