// eslint-disable-next-line
const debounce = (fn, timeout) => {
  let timeoutId;

  return function(...args) {
    const context = this;
    clearTimeout(timeoutId);

    timeoutId = setTimeout(() => {
      fn.call(context, ...args);
    }, timeout);
  };
};
