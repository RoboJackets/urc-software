(function(exports) {
  // To help us identify that the annotation is of type Triangle
  const TRIANGLE_ANNOT_ID = 'triangle';
  const ANNOT_TYPE = 'AnnotType;';

  function TriangleAnnotationFactory(Annotations, Math) {
    class TriangleAnnotation extends Annotations.CustomAnnotation {
      constructor() {
        super('triangle');
        this.Subject = 'Triangle';
        this[ANNOT_TYPE] = TRIANGLE_ANNOT_ID;
        this.vertices = [];
        const numVertices = 3;
        for (let i = 0; i < numVertices; ++i) {
          this.vertices.push(new Math.Point());
        }
        this.selectionModel = exports.TriangleSelectionModelFactory.initialize(Annotations, Math);
      }

      draw(ctx, pageMatrix) {
        // the setStyles function is a function on markup annotations that sets up
        // certain properties for us on the canvas for the annotation's stroke thickness.
        this.setStyles(ctx, pageMatrix);
        // draw the triangle lines using vertices from our list
        ctx.beginPath();
        ctx.moveTo(this.vertices[0].x, this.vertices[0].y);
        ctx.lineTo(this.vertices[1].x, this.vertices[1].y);
        ctx.lineTo(this.vertices[2].x, this.vertices[2].y);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
      }
      resize(rect) {
        // this function is only called when the annotation is dragged
        // since we handle the case where the control handles move
        const annotRect = this.getRect();
        // determine how much change in each dimension
        const deltaX = rect.x1 - annotRect.x1;
        const deltaY = rect.y1 - annotRect.y1;
        // shift the vertices by the amount the rect has shifted
        this.vertices.forEach(vertex => vertex.translate(deltaX, deltaY));
        this.setRect(rect);
      }

      serialize(element, pageMatrix) {
        const el = super.serialize(element, pageMatrix);
        // create an attribute to save the vertices list
        el.setAttribute('vertices', Annotations.XfdfUtils.serializePointArray(this.vertices, pageMatrix));
        return el;
      }

      deserialize(element, pageMatrix) {
        super.deserialize(element, pageMatrix);
        // read it back as points from the attribute
        this.vertices = Annotations.XfdfUtils.deserializePointArray(element.getAttribute('vertices'), pageMatrix);
      }
    }

    TriangleAnnotation.SerializationType = Annotations.CustomAnnotation.SerializationTypes.STAMP; // use custom XFDF
    // this is necessary to set the elementName before instantiation
    TriangleAnnotation.prototype.elementName = 'triangle';

    return TriangleAnnotation;
  }

  exports.TriangleAnnotationFactory = {
    initialize: TriangleAnnotationFactory,
    TRIANGLE_ANNOT_ID,
    ANNOT_TYPE,
  };
})(window);
