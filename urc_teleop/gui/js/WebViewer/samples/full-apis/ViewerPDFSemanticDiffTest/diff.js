(async exports => {
  const Core = exports.Core;
  const PDFNet = exports.Core.PDFNet;
  Core.setWorkerPath('../../../lib/core');
  Core.enableFullPDF();
  await PDFNet.initialize();

  const parentDoc = window.parent.window.document;

  // Replace with your license key here as it needs to be passed when instantiating the worker transport promise
  const licenseKey = undefined;

  // Shared worker
  const workerTransportPromise = Core.initPDFWorkerTransports('pdf', {}, licenseKey);

  const containers = ['viewer1', 'viewer2'];
  const instances = [];
  const initialFiles = ['/samples/files/semantic_test_doc_1.pdf', '/samples/files/semantic_test_doc_2.pdf'];

  let scrollTimeout = null;
  let originalScroller = null;

  const initializeViewer = containerName => {
    return new Promise(resolve => {
      WebViewer(
        {
          path: '../../../lib',
          // Use shared worker
          workerTransportPromise,
          fullAPI: true,
        },
        document.getElementById(containerName)
      ).then(instance => {
        instance.Core.syncNamespaces({ PDFNet });

        instance.Core.documentViewer.addEventListener('documentLoaded', () => {
          const scrollView = instance.Core.documentViewer.getScrollViewElement();
          scrollView.onscroll = function() {
            if (!originalScroller || originalScroller === scrollView) {
              originalScroller = scrollView;
              const leftPercentage = scrollView.scrollLeft / scrollView.scrollWidth;
              const topPercentage = scrollView.scrollTop / scrollView.scrollHeight;
              syncDocumentContainerScrolls(leftPercentage, topPercentage);
              clearTimeout(scrollTimeout);
              scrollTimeout = setTimeout(() => {
                originalScroller = null;
              }, 50);
            }
          };

          // Update zoom value of the WebViewer instances
          instance.Core.documentViewer.addEventListener('zoomUpdated', zoom => {
            // zoom events will also trigger a scroll event
            // set the original scroll to be the same panel that first triggers the zoom event
            // so that scroll events are handled properly and in the correct order
            // some browsers such as Chrome do not respect the scroll event ordering correctly
            if (!originalScroller) {
              originalScroller = scrollView;
              clearTimeout(scrollTimeout);
              scrollTimeout = setTimeout(() => {
                originalScroller = null;
              }, 50);
            }
            syncZoom(zoom);
          });

          instance.Core.documentViewer.addEventListener('rotationUpdated', rotation => {
            syncRotation(rotation);
          });
        });

        instances.push(instance);
        resolve(instance);
      });
    });
  };

  const main = async () => {
    const initTasks = containers.map(containerName => initializeViewer(containerName));

    const docTasks = initialFiles.map(initialFile => PDFNet.PDFDoc.createFromURL(initialFile));

    await Promise.all([...initTasks, ...docTasks]);
    const docs = await Promise.all(docTasks);

    await compareDoc(docs[0], docs[1]);

    parentDoc.getElementById('fileUpload1').disabled = false;
    parentDoc.getElementById('fileUpload2').disabled = false;
    const compareButton = parentDoc.getElementById('compareButton');
    compareButton.addEventListener('click', async () => {
      const doc1 = uploadedDoc[0];
      const doc2 = uploadedDoc[1];
      disableCompareButton();
      await compareDoc(doc1, doc2);
    });
  };

  main();

  const uploadedDoc = [null, null];
  const recentDiffs = [];

  const syncDocumentContainerScrolls = (scrollLeftPercentage, scrollTopPercentage) => {
    instances.forEach(instance => {
      const scrollView = instance.docViewer.getScrollViewElement();
      if (!scrollView) {
        return;
      }
      const currentLeftPosition = scrollView.scrollLeft / scrollView.scrollWidth;
      const currentTopPosition = scrollView.scrollTop / scrollView.scrollHeight;
      if (currentLeftPosition !== scrollLeftPercentage) {
        scrollView.scrollLeft = scrollView.scrollWidth * scrollLeftPercentage;
      }
      if (currentTopPosition !== scrollTopPercentage) {
        scrollView.scrollTop = scrollView.scrollHeight * scrollTopPercentage;
      }
    });
  };

  const syncZoom = zoom => {
    instances.forEach(instance => {
      if (instance.UI.getZoomLevel() !== zoom) {
        instance.UI.setZoomLevel(zoom);
      }
    });
  };

  const syncRotation = rotation => {
    instances.forEach(instance => {
      const documentViewer = instance.docViewer;
      if (documentViewer.getRotation() !== rotation) {
        documentViewer.setRotation(rotation);
      }
    });
  };

  const compareDoc = async (doc1, doc2) => {
    const leftPageCount = await doc1.getPageCount();
    const rightPageCount = await doc2.getPageCount();

    const leftDoc = await PDFNet.PDFDoc.create();
    leftDoc.lock();

    const rightDoc = await PDFNet.PDFDoc.create();
    rightDoc.lock();

    const newDoc = await PDFNet.PDFDoc.create();
    newDoc.lock();

    await newDoc.appendTextDiffDoc(doc1, doc2);

    const totalPageCount = await newDoc.getPageCount();
    const isLeftDocLarger = leftPageCount > rightPageCount;
    const smallerCount = leftPageCount > rightPageCount ? leftPageCount : rightPageCount;

    for (let i = 0; i < totalPageCount; i++) {
      const page = await newDoc.getPage(i + 1);
      if (i === smallerCount) {
        if (isLeftDocLarger) {
          await leftDoc.pagePushBack(page);
        } else {
          await rightDoc.pagePushBack(page);
        }
        continue;
      }
      if (i % 2 === 0) {
        await leftDoc.pagePushBack(page);
      } else {
        await rightDoc.pagePushBack(page);
      }
    }

    await newDoc.unlock();
    await leftDoc.unlock();
    await rightDoc.unlock();

    instances[0].UI.loadDocument(leftDoc);
    instances[1].UI.loadDocument(rightDoc);

    recentDiffs.push([...uploadedDoc]);

    // Skip default comparison
    if (recentDiffs.length === 1) {
      return;
    }

    const recentElement = parentDoc.getElementById('recentFiles');
    const comparisonElement = document.createElement('button');
    comparisonElement.innerText = `Compare ${doc1.fileName} (A) & ${doc2.fileName} (B)`;
    comparisonElement.classList.add('link');
    comparisonElement.onclick = onClickRecentLink.bind({ idx: recentDiffs.length - 1 });
    recentElement.appendChild(comparisonElement);
  };

  const enableCompareButton = async () => {
    const compareButton = parentDoc.getElementById('compareButton');

    if (!compareButton.classList.contains('disabled')) {
      return;
    }

    compareButton.classList.remove('disabled');
  };

  const disableCompareButton = async () => {
    const compareButton = parentDoc.getElementById('compareButton');

    if (compareButton.classList.contains('disabled')) {
      return;
    }

    compareButton.classList.add('disabled');
  };

  const getPDFDocFromUpload = async (file, fileIndex) => {
    const newDoc = await Core.createDocument(file, {});
    uploadedDoc[fileIndex] = await newDoc.getPDFDoc();
    uploadedDoc[fileIndex].fileName = file.name;
    if (uploadedDoc[1] !== null && uploadedDoc[0] !== null) {
      enableCompareButton();
    }
  };

  parentDoc.getElementById('fileUpload1').addEventListener('change', e => {
    getPDFDocFromUpload(e.target.files[0], 0);
  });

  parentDoc.getElementById('fileUpload2').addEventListener('change', e => {
    getPDFDocFromUpload(e.target.files[0], 1);
  });

  const onClickRecentLink = async function() {
    await compareDoc(recentDiffs[this.idx][0], recentDiffs[this.idx][1]);
  };
})(window);
// eslint-disable-next-line spaced-comment
//# sourceURL=config.js
