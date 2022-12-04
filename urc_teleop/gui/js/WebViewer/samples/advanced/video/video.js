/* eslint-disable */
const viewerElement = document.getElementById('viewer');
const DOCUMENT_ID = 'video';
const DEFAULT_ZOOM = 1.25;

WebViewer(
  {
    path: 'lib',
    css: 'styles.css',
    disabledElements: ['searchButton', 'pageNavOverlay', 'viewControlsButton', 'panToolButton'],
  },
  viewerElement
).then(async instance => {
  const { Core, UI } = instance;
  const { documentViewer } = Core;
  const { iframeWindow } = UI;
  const theme = UI.Theme;
  instance.UI.setTheme(theme.DARK);
  const annotationManager = documentViewer.getAnnotationManager();

  const license = `---- Insert commercial license key here after purchase ----`;

  // Extends document class to support documents of type 'video'
  await WebViewer.Video.registerDocument(instance, license);

  // Load a video at a specific url. This file needs to be relative to lib/ui/index.html.
  const videoUrl = 'https://pdftron.s3.amazonaws.com/downloads/pl/video/video.mp4';
  const thumbnail = 'https://pdftron.s3.amazonaws.com/downloads/pl/video/thumbnail.jpg';
  WebViewer.Video.loadDocument(videoUrl, thumbnail);

  // Add save annotations button
  UI.setHeaderItems(header => {
    header.push({
      type: 'actionButton',
      img:
        '<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24"><path d="M0 0h24v24H0z" fill="none"/><path d="M17 3H5c-1.11 0-2 .9-2 2v14c0 1.1.89 2 2 2h14c1.1 0 2-.9 2-2V7l-4-4zm-5 16c-1.66 0-3-1.34-3-3s1.34-3 3-3 3 1.34 3 3-1.34 3-3 3zm3-10H5V5h10v4z"/></svg>',
      onClick: async () => {
        // Save annotations when button is clicked
        // widgets and links will remain in the document without changing so it isn't necessary to export them

        // Make a POST request with XFDF string
        const saveXfdfString = (documentId, xfdfString) => {
          return new Promise(resolve => {
            fetch(`/server/annotationHandler.js?documentId=${documentId}`, {
              method: 'POST',
              body: xfdfString,
            }).then(response => {
              if (response.status === 200) {
                resolve();
              }
            });
          });
        };

        const annotations = documentViewer
          .getDocument()
          .getVideo()
          .getAllAnnotations();
        const xfdfString = await annotationManager.exportAnnotations({ links: false, widgets: false, annotList: annotations });
        await saveXfdfString(DOCUMENT_ID, xfdfString);
        alert('Annotations saved successfully.');
      },
    });
  });

  // Load saved annotations
  documentViewer.addEventListener('documentLoaded', () => {
    documentViewer.zoomTo(DEFAULT_ZOOM);
    const doc = documentViewer.getDocument();
    const video = documentViewer.getDocument().getVideo();

    // Make a GET request to get XFDF string
    const loadXfdfString = documentId => {
      return new Promise(resolve => {
        fetch(`/server/annotationHandler.js?documentId=${documentId}`, {
          method: 'GET',
        }).then(response => {
          if (response.status === 200) {
            response.text().then(xfdfString => {
              console.log(xfdfString);
              resolve(xfdfString);
            });
          } else if (response.status === 204) {
            console.warn(`Found no content in xfdf file /server/annotationHandler.js?documentId=${documentId}`);
            resolve('');
          } else {
            console.warn(`Something went wrong trying to load xfdf file /server/annotationHandler.js?documentId=${documentId}`);
            console.warn(`Response status ${response.status}`);
            resolve('');
          }
        });
      });
    };

    loadXfdfString(DOCUMENT_ID)
      .then(xfdfString => {
        const annotationManager = documentViewer.getAnnotationManager();
        return annotationManager.importAnnotations(xfdfString);
      })
      .then(() => {
        video.updateAnnotationsToTime(0);
      });
  });

  let once = false;
  // Create the video UI controls
  documentViewer.addEventListener('pageComplete', (pageIndex, videoContainer) => {
    if (once) return;
    once = true;
    const createElementFromHTML = htmlString => {
      const div = document.createElement('div');
      div.innerHTML = htmlString.trim();

      return div.firstChild;
    };

    const doc = documentViewer.getDocument();
    const video = doc.getVideo();
    const controls = createElementFromHTML(`
        <div class="controls">
            <div class="buttons-container">
              <div class="video-buttons">
                <svg id="play" class="icon" width="18px" height="18px" data-state="hidden">
                  <path d="M15.562 8.1L3.87.225c-.818-.562-1.87 0-1.87.9v15.75c0 .9 1.052 1.462 1.87.9L15.563 9.9c.584-.45.584-1.35 0-1.8z"/>
                </svg>
                <svg id="pause" class="icon" width="18px" height="18px" data-state="hidden">
                  <path d="M6 1H3c-.6 0-1 .4-1 1v14c0 .6.4 1 1 1h3c.6 0 1-.4 1-1V2c0-.6-.4-1-1-1zm6 0c-.6 0-1 .4-1 1v14c0 .6.4 1 1 1h3c.6 0 1-.4 1-1V2c0-.6-.4-1-1-1h-3z"/>
                </svg>
                <svg id="volume" class="icon" width="20px" height="18px" data-state="visible">
                  <path d="M15.6 3.3c-.4-.4-1-.4-1.4 0-.4.4-.4 1 0 1.4C15.4 5.9 16 7.4 16 9c0 1.6-.6 3.1-1.8 4.3-.4.4-.4 1 0 1.4.2.2.5.3.7.3.3 0 .5-.1.7-.3C17.1 13.2 18 11.2 18 9s-.9-4.2-2.4-5.7z"/>
                  <path d="M11.282 5.282a.909.909 0 0 0 0 1.316c.735.735.995 1.458.995 2.402 0 .936-.425 1.917-.995 2.487a.909.909 0 0 0 0 1.316c.145.145.636.262 1.018.156a.725.725 0 0 0 .298-.156C13.773 11.733 14.13 10.16 14.13 9c0-.17-.002-.34-.011-.51-.053-.992-.319-2.005-1.522-3.208a.909.909 0 0 0-1.316 0zm-7.496.726H.714C.286 6.008 0 6.31 0 6.76v4.512c0 .452.286.752.714.752h3.072l4.071 3.858c.5.3 1.143 0 1.143-.602V2.752c0-.601-.643-.977-1.143-.601L3.786 6.008z"/>
                </svg>
                <svg id="muted" class="icon" width="20px" height="18px" data-state="visible">
                  <path d="M12.4 12.5l2.1-2.1 2.1 2.1 1.4-1.4L15.9 9 18 6.9l-1.4-1.4-2.1 2.1-2.1-2.1L11 6.9 13.1 9 11 11.1zM3.786 6.008H.714C.286 6.008 0 6.31 0 6.76v4.512c0 .452.286.752.714.752h3.072l4.071 3.858c.5.3 1.143 0 1.143-.602V2.752c0-.601-.643-.977-1.143-.601L3.786 6.008z"/>
                </svg>
              </div>
              <div class="video-buttons">
                <span class="time" id="current-time">00:00:00</span>
                <svg style="display: none;" class="icon" width="18px" height="18px">
                  <path d="M16.135 7.784a2 2 0 0 1-1.23-2.969c.322-.536.225-.998-.094-1.316l-.31-.31c-.318-.318-.78-.415-1.316-.094a2 2 0 0 1-2.969-1.23C10.065 1.258 9.669 1 9.219 1h-.438c-.45 0-.845.258-.997.865a2 2 0 0 1-2.969 1.23c-.536-.322-.999-.225-1.317.093l-.31.31c-.318.318-.415.781-.093 1.317a2 2 0 0 1-1.23 2.969C1.26 7.935 1 8.33 1 8.781v.438c0 .45.258.845.865.997a2 2 0 0 1 1.23 2.969c-.322.536-.225.998.094 1.316l.31.31c.319.319.782.415 1.316.094a2 2 0 0 1 2.969 1.23c.151.607.547.865.997.865h.438c.45 0 .845-.258.997-.865a2 2 0 0 1 2.969-1.23c.535.321.997.225 1.316-.094l.31-.31c.318-.318.415-.781.094-1.316a2 2 0 0 1 1.23-2.969c.607-.151.865-.547.865-.997v-.438c0-.451-.26-.846-.865-.997zM9 12a3 3 0 1 1 0-6 3 3 0 0 1 0 6z"/>
                </svg>
              </div>
            </div>
            <div class="timeline">
              <div class="markers"></div>
              <progress id="progress">
              </progress>
              <div class="tooltip" id="tooltip">
                00:00:00
              </div>
            </div>
            </div>
        </div>
      `);

    videoContainer.appendChild(controls);
    const play = controls.querySelector('#play');
    const pause = controls.querySelector('#pause');
    const volume = controls.querySelector('#volume');
    const muted = controls.querySelector('#muted');
    const progress = controls.querySelector('#progress');
    const markers = controls.querySelector('.markers');
    const currentTime = controls.querySelector('#current-time');
    const tooltip = controls.querySelector('#tooltip');

    const videoElement = video.getElement();
    const showMarkers = annotations => {
      while (markers.firstChild) {
        markers.removeChild(markers.firstChild);
      }
      annotations.forEach(annotation => {
        if (annotation.startTime <= video.duration) {
          const marker = document.createElement('div');
          marker.className = 'marker';
          const percent = annotation.startTime / video.duration;
          marker.onclick = () => {
            goToTime(annotation.startTime);
          };
          const markerLeft = Math.floor(percent * progress.clientWidth) - 1;
          marker.style = `left: ${markerLeft}px`;
          markers.appendChild(marker);
        }
      });
    };
    annotationManager.addEventListener('annotationChanged', () => {
      showMarkers(video.getAllAnnotations());
    });
    showMarkers(video.getAllAnnotations());

    play.setAttribute('data-state', 'visible');
    pause.setAttribute('data-state', 'hidden');
    videoElement.addEventListener('play', () => {
      play.setAttribute('data-state', 'hidden');
      pause.setAttribute('data-state', 'visible');
    });
    videoElement.addEventListener('pause', () => {
      play.setAttribute('data-state', 'visible');
      pause.setAttribute('data-state', 'hidden');
    });
    play.addEventListener('click', () => {
      if (videoElement.paused || videoElement.ended) {
        videoElement.play();
      }
    });
    pause.addEventListener('click', () => {
      videoElement.pause();
    });

    volume.setAttribute('data-state', 'visible');
    muted.setAttribute('data-state', 'hidden');
    videoElement.addEventListener('volumechange', e => {
      if (videoElement.muted) {
        volume.setAttribute('data-state', 'hidden');
        muted.setAttribute('data-state', 'visible');
      } else {
        volume.setAttribute('data-state', 'visible');
        muted.setAttribute('data-state', 'hidden');
      }
    });
    volume.addEventListener('click', () => {
      videoElement.muted = true;
    });
    muted.addEventListener('click', () => {
      videoElement.muted = false;
    });

    progress.setAttribute('max', video.duration);

    const timelineFrames = createElementFromHTML(`
        <div id="timeline-frames" class="timeline-frames">
      `);

    let frameCanvases = {};
    const onScroll = async () => {
      const { x: timelineX, width: timelineWidth } = timelineFrames.getBoundingClientRect();

      const innerFrames = Array.from(timelineFrames.getElementsByClassName('innerFrame')).filter(innerFrame => {
        const { x: frameX, width: frameWidth } = innerFrame.getBoundingClientRect();
        const isVisible = frameX + frameWidth > timelineX && frameX < timelineX + timelineWidth;
        return innerFrame.children.length === 0 && isVisible;
      });
      const frameNumbers = innerFrames.map(innerFrame => innerFrame.frameNumber).filter(frameNumber => !frameCanvases[frameNumber]);

      frameCanvases = { ...frameCanvases, ...(await video.extractFrames(frameNumbers)) };
      innerFrames.forEach(innerFrame => {
        const frame = frameCanvases[innerFrame.frameNumber];
        if (frame) {
          innerFrame.appendChild(frame);
        } else {
          console.warn(`Failed to get canvas for frame: ${innerFrame.frameNumber}`);
        }
      });
    };

    timelineFrames.addEventListener('scroll', _.debounce(onScroll, 250));

    const marginRight = 8;
    const widthFrameContainer = 92.5;
    const timelineHeight = 99;
    const timelineWidth = 770 / documentViewer.getZoomLevel();

    const totalFrames = video.getTotalFrames();
    let selectedFrameContainer;
    HyperList.create(timelineFrames, {
      height: timelineHeight,
      width: timelineWidth,
      horizontal: true,
      itemHeight: marginRight + widthFrameContainer,
      total: totalFrames,
      generate(index) {
        const frameNumber = index + 1;
        const frameContainer = document.createElement('div');
        frameContainer.id = `frame${frameNumber}`;
        frameContainer.className = 'frame';
        const innerFrameContainer = document.createElement('div');
        innerFrameContainer.id = `innerFrame${frameNumber}`;
        innerFrameContainer.frameNumber = frameNumber;
        innerFrameContainer.className = 'innerFrame';
        innerFrameContainer.style = `min-width: ${88}px; min-height: ${50}px;`;

        frameContainer.onclick = () => {
          goToTime(video.getTimeFromFrame(frameNumber));
        };

        const frameFooter = createElementFromHTML(`
            <div class="frameFooter">
              <div class="frameNumber">
                <span>${video.getFormattedTime(video.getTimeFromFrame(frameNumber))}</span>
              </div>
            </div>
          `);

        // if (video.hasAnnotation(frameNumber)) {
        //   const pencilIcon = createElementFromHTML(`
        //     <svg width="18px" height="18px" viewBox="0 0 24 24">
        //       <use xlink:href="./plyr/plyr.svg#pencil"></use>
        //     </svg>
        //   `);
        //   frameFooter.insertBefore(pencilIcon, frameFooter.firstChild);
        // }

        const frame = frameCanvases[frameNumber];
        if (frame && frame !== 'inprogress') {
          innerFrameContainer.appendChild(frame);
        }

        frameContainer.appendChild(innerFrameContainer);
        frameContainer.appendChild(frameFooter);

        const currentFrameNumber = video.getFrameFromTime(videoElement.currentTime);

        if (frameNumber === currentFrameNumber) {
          frameContainer.setAttribute('data-state', 'selected');
          selectedFrameContainer = frameContainer;
        }
        return frameContainer;
      },
    });

    controls.appendChild(timelineFrames);
    videoElement.addEventListener('timeupdate', async () => {
      doc.getVideo().updateAnnotationsToTime(videoElement.currentTime);

      if (selectedFrameContainer) {
        selectedFrameContainer.removeAttribute('data-state');
      }

      const currentFrameNumber = video.getFrameFromTime(videoElement.currentTime);
      selectedFrameContainer = iframeWindow.document.getElementById(`frame${currentFrameNumber}`);
      if (selectedFrameContainer) {
        selectedFrameContainer.setAttribute('data-state', 'selected');
      }
    });

    const goToTime = time => {
      videoElement.currentTime = time;

      progress.value = videoElement.currentTime;

      currentTime.innerHTML = `${video.getFormattedCurrentTime()}`;
      const currentFrameNumber = video.getFrameFromTime(videoElement.currentTime);

      const rightmostPosition = (currentFrameNumber - 1) * (marginRight + widthFrameContainer);
      const scrollLeft = rightmostPosition - timelineFrames.clientWidth / 2 + widthFrameContainer / 2;
      if (Math.abs(timelineFrames.scrollLeft - scrollLeft) < 800) {
        timelineFrames.scroll({
          left: scrollLeft,
          behavior: 'smooth',
        });
      } else {
        timelineFrames.scrollLeft = scrollLeft;
      }
    };

    let stateCurrentTime;
    progress.addEventListener('click', e => {
      goToTime(stateCurrentTime);
    });

    tooltip.setAttribute('data-state', 'hidden');
    progress.addEventListener('mousemove', e => {
      const { width } = progress.getBoundingClientRect();
      const percentage = (e.offsetX * documentViewer.getZoom()) / width;
      const newTime = percentage * progress.max;
      stateCurrentTime = newTime;

      tooltip.setAttribute('data-state', 'visible');
      tooltip.style = `left: ${e.offsetX}px;`;
      tooltip.innerHTML = `${video.getFormattedTime(newTime)}`;
    });
    progress.addEventListener('mouseout', e => {
      tooltip.setAttribute('data-state', 'hidden');
    });

    onScroll();
  });
});
