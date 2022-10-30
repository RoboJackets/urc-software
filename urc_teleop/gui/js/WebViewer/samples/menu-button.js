const headerElement = document.getElementsByTagName('header')[0];
const asideElement = document.getElementsByTagName('aside')[0];

const menuButton = document.createElement('div');
menuButton.className = 'menu';
menuButton.onclick = function() {
  if (asideElement.style.display === 'block') {
    asideElement.style.display = 'none';
  } else {
    asideElement.style.display = 'block';
  }
};

const div = document.createElement('div');
menuButton.appendChild(div);
menuButton.appendChild(div.cloneNode());
menuButton.appendChild(div.cloneNode());

headerElement.appendChild(menuButton);
