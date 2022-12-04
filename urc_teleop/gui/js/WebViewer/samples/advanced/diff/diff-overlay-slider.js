(function(exports) {
  let enabled;
  let value;

  function enable(enbled) {
    enabled = enbled;
  }

  function isEnabled() {
    return enabled;
  }

  function setValue(val) {
    if (val >= 0 && val <= 1) {
      value = val;
    } else {
      throw new Error('value must be a decimal between 0 - 1 (inclusive)');
    }
  }

  function getValue() {
    return value;
  }

  exports.DiffOverlaySlider = {
    enable,
    isEnabled,
    setValue,
    getValue,
  };
})(window);
