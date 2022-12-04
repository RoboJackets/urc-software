WebViewer(
  {
    path: '../../../lib',
    initialDoc: '../../full-apis/TestFiles/contract.pdf',
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);

  instance.setToolbarGroup('toolbarGroup-Forms');
});
