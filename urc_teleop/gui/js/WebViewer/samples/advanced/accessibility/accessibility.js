let voiceIndex = 0;
let pitch = 1;
let rate = 1;
let volume = 1;

window.onbeforeunload = () => {
  if (speechSynthesis) {
    speechSynthesis.cancel();
  }
};

const readText = documentText => {
  const utterance = new SpeechSynthesisUtterance(documentText);
  if (voiceIndex) {
    utterance.voice = speechSynthesis.getVoices()[voiceIndex];
  }
  utterance.pitch = pitch;
  utterance.rate = rate;
  utterance.volume = volume;
  if (speechSynthesis.speaking) {
    speechSynthesis.resume();
  } else {
    speechSynthesis.speak(utterance);
  }
};

const pauseText = () => {
  speechSynthesis.pause();
};

const addVoices = () => {
  for (let i = 0; i < speechSynthesis.getVoices().length; i++) {
    const voice = speechSynthesis.getVoices()[i];
    const option = document.createElement('option');
    // eslint-disable-next-line
    option.textContent = `${voice.voiceURI}-${voice.lang}`;
    option.value = i;
    document.getElementById('voice').appendChild(option);
  }
};

// Instantiate
WebViewer(
  {
    path: '../../../lib',
    initialDoc: '../../../samples/files/cheetahs.pdf',
    accessibleMode: true,
  },
  document.getElementById('viewer')
).then(instance => {
  samplesSetup(instance);
  const documentViewer = instance.Core.documentViewer;
  const iframeDocument = instance.UI.iframeWindow.document;

  const getPageText = pageNumber => {
    const pageTextElement = iframeDocument.getElementById(`pageText${pageNumber}`);
    return pageTextElement ? pageTextElement.innerText : null;
  };

  let intervalId;
  const readDocumentText = () => {
    speechSynthesis.cancel();
    clearInterval(intervalId);
    // setInterval used in case text DOM is not ready yet
    intervalId = setInterval(() => {
      const text = getPageText(documentViewer.getCurrentPage());

      if (text) {
        readText(text);
        clearInterval(intervalId);
      }
    }, 200);
  };

  documentViewer.addEventListener('documentLoaded', () => {
    const playButton = document.getElementById('play');
    const pauseButton = document.getElementById('pause');

    iframeDocument.addEventListener('keydown', e => {
      if (e.key === 'Tab' || e.keycode === 9) {
        speechSynthesis.cancel();
      }
      if (e.key === 'p' || e.keycode === 80) {
        readDocumentText();
      }
    });

    const voiceList = window.speechSynthesis.getVoices();
    if (voiceList.length) {
      addVoices();
    } else {
      window.speechSynthesis.onvoiceschanged = addVoices;
    }

    playButton.onclick = readDocumentText;
    pauseButton.onclick = pauseText;
  });
});

const isIE11 = !!window.MSInputMethodContext && !!document.documentMode;

// SpeechSynthesis is not supported in IE11
if (isIE11) {
  window.alert('SpeechSynthesis is not supported in IE11.\nPlease try a different browser.');
  const aside = document.getElementsByTagName('aside')[0];
  while (aside.firstChild) {
    aside.removeChild(aside.firstChild);
  }
  const warningMessage = document.createTextNode('This demo is not compatible with IE11. Please open the demo in a different browser or ');
  const returnLink = document.createElement('a');
  const returnText = document.createTextNode('go back to samples');
  returnLink.setAttribute('href', '../');
  returnLink.setAttribute('target', '_self');
  aside.appendChild(warningMessage);
  returnLink.appendChild(returnText);
  aside.appendChild(returnLink);
}

const voiceDropdown = document.getElementById('voice');
const pitchSlider = document.getElementById('pitch');
const rateSlider = document.getElementById('rate');
const volumeSlider = document.getElementById('volume');

voiceDropdown.onchange = e => {
  speechSynthesis.cancel();
  voiceIndex = e.target.value;
};
pitchSlider.onchange = e => {
  speechSynthesis.cancel();
  pitch = e.target.value / 50;
};
rateSlider.onchange = e => {
  speechSynthesis.cancel();
  rate = e.target.value / 10;
};
volumeSlider.onchange = e => {
  speechSynthesis.cancel();
  volume = e.target.value / 100;
};
