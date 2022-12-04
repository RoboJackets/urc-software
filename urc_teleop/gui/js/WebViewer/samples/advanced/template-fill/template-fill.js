let editor;
let viewedDocSchema = {};
let annotations = [];
let annotationsByTag = {};

const sampleFilePath = {
  'SYH-letter': '../../samples/files/template-SYH-letter.docx',
  'invoice-simple': '../../samples/files/template-invoice-simple.docx',
  'invoice-complex': '../../samples/files/template-invoice-complex.docx',
};
const queryDoc = new URLSearchParams(window.location.search).get('doc');
if (queryDoc in sampleFilePath) {
  document.getElementById('samples-file-picker').value = queryDoc;
}
let viewingFile = document.getElementById('samples-file-picker').value || 'SYH-letter';

WebViewer(
  {
    path: '../../../lib',
    preloadWorker: 'office',
    fullAPI: false,
    css: 'webviewer.css',
  },
  document.getElementById('viewer')
).then(instance => {
  const { UI, Core } = instance;
  const { documentViewer } = instance.Core;

  UI.disableFeatures(UI.Feature.Annotations);

  loadDoc();

  async function loadDoc() {
    updateFileStatus();
    // Loading the template document with doTemplatePrep, so that we can access the schema and bounding boxes:
    await instance.loadDocument(sampleFilePath[viewingFile] || viewingFile, {
      officeOptions: {
        doTemplatePrep: true,
      },
      onError: pageModificationsAfterLoadError,
    });
  }

  async function generateDocument() {
    const templateValues = editor.getValue();
    convertLinks(templateValues);
    instance.UI.closeElements('errorModal');
    // Fill the template document with the data from templateValues:
    await documentViewer
      .getDocument()
      .applyTemplateValues(templateValues)
      .then(updateAnnotations)
      .catch(e => UI.displayErrorMessage(e.message));
  }

  documentViewer.addEventListener('documentLoaded', async () => {
    // Get the schema of the template keys used in the document:
    const schema = await documentViewer
      .getDocument()
      .getTemplateKeys('schema')
      .catch(e => UI.displayErrorMessage(e.message));
    const jsonSchema = templateSchemaToJsonSchema(schema);
    await updateAnnotations(instance);

    if (!editor || JSON.stringify(schema) !== JSON.stringify(viewedDocSchema)) {
      viewedDocSchema = schema;
      const options = {
        theme: 'pdftron',
        iconlib: 'pdftron',
        schema: jsonSchema,
        prompt_before_delete: false,
        disable_properties: true,
        disable_array_reorder: true,
        disable_array_delete_last_row: true,
        disable_array_delete_all_rows: true,
        expand_height: true,
        keep_oneof_values: false,
      };
      if (viewingFile in prePopulateData) {
        options.startval = prePopulateData[viewingFile];
      }
      if (editor) {
        editor.destroy();
      }
      editor = new JSONEditor(document.getElementById('autofill-form'), options);
      viewedDocSchema = schema;
      editor.on('ready', pageModificationsAfterLoad);
      editor.on('ready', addEventHandlersToJsonEditor);
      editor.on('addRow', addEventHandlersToJsonEditor);
    } else {
      // We already have an editor with the correct schema.
      pageModificationsAfterLoad();
    }
  });

  class UnselectableSelectionModel extends Core.Annotations.SelectionModel {
    constructor(annotation) {
      super(annotation, false);
    }
    drawSelectionOutline() {}
    testSelection() {
      return false;
    }
  }

  async function updateAnnotations() {
    Core.annotationManager.deleteAnnotations(annotations, true);
    annotations = [];
    annotationsByTag = {};
    const fillColor = new Core.Annotations.Color(255, 255, 0, 0.2);
    const strokeColor = new Core.Annotations.Color(150, 150, 0, 1);
    // Get the bounding boxes of the template keys in the document:
    const boundingBoxes = await documentViewer
      .getDocument()
      .getTemplateKeys('locations')
      .catch(e => UI.displayErrorMessage(e.message));
    if (boundingBoxes) {
      for (const tag in boundingBoxes) {
        for (const boundingBox of boundingBoxes[tag]) {
          const pageNum = boundingBox[0];
          const rect = boundingBox[1];
          const annotationRect = new Core.Math.Rect(rect.x1 - 2, rect.y1 - 2, rect.x2 + 2, rect.y2 + 2);
          const annotation = new Core.Annotations.RectangleAnnotation();
          annotation.setRect(annotationRect);
          annotation.setPageNumber(pageNum);
          annotation.FillColor = fillColor;
          annotation.StrokeColor = strokeColor;
          annotation.StrokeThickness = 1;
          annotation.selectionModel = UnselectableSelectionModel;
          annotation.Hidden = true;
          annotations.push(annotation);
          if (!annotationsByTag.hasOwnProperty(tag)) {
            annotationsByTag[tag] = [];
          }
          annotationsByTag[tag].push(annotation);
        }
      }
    }
    Core.annotationManager.addAnnotations(annotations, true);
    Core.annotationManager.drawAnnotationsFromList(annotations);
  }

  function showAnnotationsForTemplateTag(templateTag) {
    const annotations = annotationsByTag[templateTag];
    if (annotations && documentViewer.getDocument()) {
      Core.annotationManager.showAnnotations(annotations);
      const visiblePages = documentViewer
        .getDisplayModeManager()
        .getDisplayMode()
        .getVisiblePages(0.0);
      for (const annotation of annotations) {
        if (visiblePages.includes(annotation.getPageNumber())) {
          return;
        }
      }
      Core.annotationManager.jumpToAnnotation(annotations[0]);
    }
  }

  function hideAnnotationsForTemplateTag(templateTag) {
    const annotations = annotationsByTag[templateTag];
    if (annotations && documentViewer.getDocument()) {
      Core.annotationManager.hideAnnotations(annotations);
    }
  }

  function addEventHandlersToJsonEditor() {
    for (const el of document.querySelectorAll('[data-template-path]')) {
      if (!el || el.getAttribute('data-has-annotation-listeners') === 'true') {
        continue;
      }
      el.setAttribute('data-has-annotation-listeners', 'true');
      const templatePath = el.getAttribute('data-template-path');
      const showAnnotationsFunc = showAnnotationsForTemplateTag.bind(null, templatePath);
      const hideAnnotationsFunc = hideAnnotationsForTemplateTag.bind(null, templatePath);
      const mouseEl = el.getAttribute('data-schematype') === 'array' ? el.firstChild : el;
      mouseEl.addEventListener('mouseenter', showAnnotationsFunc);
      mouseEl.addEventListener('mouseleave', hideAnnotationsFunc);
    }
  }

  document.getElementById('file-picker').onchange = e => {
    const file = e.target.files[0];
    if (file) {
      document.getElementById('samples-file-picker').selectedIndex = 0;
      viewingFile = file;
      loadDoc();
    }
  };
  document.getElementById('samples-file-picker').onchange = e => {
    viewingFile = e.target.value;
    loadDoc();
  };
  document.getElementById('reset-document-button').onclick = loadDoc;
  document.getElementById('generate-document-button').onclick = async () => {
    await generateDocument();
    await generateDocument();
  };
});

function templateSchemaKeyValuesToJsonSchema(templateKV) {
  const ret = {};
  for (const key in templateKV) {
    const valTemplateSchema = templateKV[key];
    const valJsonSchema = {};
    ret[key] = valJsonSchema;
    valJsonSchema['propertyOrder'] = valTemplateSchema['docOrder'];
    switch (valTemplateSchema['typeId']) {
      case 'TemplateSchemaBool':
        valJsonSchema['$ref'] = '#/definitions/template-bool';
        break;
      case 'TemplateSchemaContent':
        valJsonSchema['$ref'] = '#/definitions/template-content';
        break;
      case 'TemplateSchemaObject':
        valJsonSchema['$ref'] = '#/definitions/template-object';
        valJsonSchema['properties'] = templateSchemaKeyValuesToJsonSchema(valTemplateSchema['properties']);
        break;
      case 'TemplateSchemaLoop':
        const loopTypeSet = new Set(valTemplateSchema['loopType']);
        valJsonSchema['$ref'] = loopTypeSet.has('tableRow') && loopTypeSet.size === 1 ? '#/definitions/template-row-loop' : '#/definitions/template-loop';
        valJsonSchema['items'] = {
          title: key,
          properties: templateSchemaKeyValuesToJsonSchema(valTemplateSchema['itemSchema']),
        };
    }
  }
  return ret;
}

function templateSchemaToJsonSchema(templateSchema) {
  return {
    $ref: '#/definitions/template-schema',
    properties: templateSchemaKeyValuesToJsonSchema(templateSchema['keys']),
    definitions: schemaDefinitions,
  };
}

function pageModificationsAfterLoadError() {
  document.getElementById('autofill-form-and-footer').className = 'autofill-form-error';
}

function pageModificationsAfterLoad() {
  document.getElementById('autofill-form-and-footer').className = '';
  document.getElementById('prep-message').style.display = 'none';
}

function updateFileStatus() {
  document.getElementById('file-status').innerText = viewingFile.name || viewingFile;
}

function convertLinks(json) {
  const referenceLinkConverter = document.getElementById('reference-link-converter');
  if (!json || typeof json !== 'object') {
    return;
  }
  if (Array.isArray(json)) {
    for (const item of json) {
      convertLinks(item);
    }
    return;
  }
  for (const entry in json) {
    if (entry === 'image_url') {
      referenceLinkConverter.href = json[entry];
      json[entry] = referenceLinkConverter.href;
    } else {
      convertLinks(json[entry]);
    }
  }
}

const prePopulateData = {
  'SYH-letter': {
    date: '07/16/21',
    land_location: '225 Parc St., Rochelle, QC ',
    lease_problem: 'According to the city records, the lease was initiated in September 2010 and never terminated',
    client: {
      full_name: 'Mrs. Eric Tragar',
      gender_possesive: 'her',
    },
    dest: {
      address: '187 Duizelstraat\n5043 EC Tilburg, Netherlands',
      given_name: 'Janice N.',
      surname: 'Symonds',
      title: 'Ms.',
    },
    sender: {
      name: 'Arnold Smith',
    },
    logo: {
      image_url: '../../files/logo_red.png',
      width: '64',
      height: '64',
    },
  },
  'invoice-simple': {
    invoice_number: 3467821,
    bill_to_name: 'Victoria Guti\u00e9rrez',
    bill_to_address: '218 Spruce Ave.\nAnna Maria, FL\n34216',
    ship_to_name: 'Mar\u00eda Rosales',
    ship_to_address: '216 E. Kennedy Blvd.\nTampa, FL\n34202',
    total_due: '430.50',
    total_paid: '150.00',
    total_owing: '280.50',
    items: [
      {
        description: 'Item 1',
        qty: 1,
        price: '10.00',
        total: '10.00',
      },
      {
        description: 'Item 2',
        qty: 20,
        price: '20.00',
        total: '400.00',
      },
      {
        description: 'Item 3',
        qty: 1,
        price: '0.00',
        total: '0.00',
      },
    ],
    subtotal: '410.00',
    sales_tax_rate: '5.0%',
    sales_tax: '20.50',
  },
  'invoice-complex': {
    invoice_number: 3467821,
    bill_to_name: 'Victoria Guti\u00e9rrez',
    bill_to_address: '218 Spruce Ave.\nAnna Maria, FL\n34216',
    ship_to_name: 'Mar\u00eda Rosales',
    ship_to_address: '216 E. Kennedy Blvd.\nTampa, FL\n34202',
    total_due: '880.50',
    total_paid: '150.00',
    total_owing: '730.50',
    pay_by_date: 'Dec 31 2021',
    pay_by_date_elapsed: false,
    vendors: [
      {
        vendor: 'OEM Corp.',
        items: [
          {
            description: 'Item 1',
            qty: 1,
            price: '10.00',
            total: '10.00',
          },
          {
            description: 'Item 2',
            qty: 20,
            price: '20.00',
            total: '400.00',
          },
        ],
        subtotal: '410.00',
        sales_tax_rate: '5.0%',
        sales_tax: '20.50',
        amount_due: '430.50',
      },
      {
        vendor: 'ABC Logistics',
        items: [
          {
            description: 'Freight, mile',
            qty: 84,
            price: '5.00',
            total: '420.00',
          },
          {
            description: 'Pickup',
            qty: 1,
            price: '30.00',
            total: '30.00',
          },
        ],
        subtotal: '450.00',
        sales_tax_rate: '5.0%',
        sales_tax: '22.50',
        discount: '-22.50',
        amount_due: '450.00',
      },
    ],
  },
};

const schemaDefinitions = {
  'template-schema': {
    type: 'object',
    title: 'Template data',
  },
  'template-bool': {
    type: 'boolean',
    format: 'checkbox',
  },
  'template-text': {
    type: 'string',
    format: 'textarea',
  },
  'template-object': {
    type: 'object',
  },
  'template-loop': {
    type: 'array',
    items: {
      type: 'object',
    },
  },
  'template-row-loop': {
    $ref: '#/definitions/template-loop',
    format: 'table',
  },
  'template-image': {
    type: 'object',
    properties: {
      image_url: {
        $ref: '#/definitions/template-text',
        propertyOrder: 1,
        format: 'url/file-download',
      },
      width: {
        type: 'string',
        title: 'width',
        propertyOrder: 2,
      },
      height: {
        type: 'string',
        title: 'height',
        propertyOrder: 3,
      },
    },
  },
  'template-markdown': {
    type: 'object',
    properties: {
      markdown: {
        $ref: '#/definitions/template-text',
      },
    },
  },
  'template-html': {
    type: 'object',
    properties: {
      html: {
        $ref: '#/definitions/template-text',
      },
    },
  },
  'template-content': {
    anyOf: [
      {
        title: 'text',
        $ref: '#/definitions/template-text',
      },
      {
        title: 'image',
        $ref: '#/definitions/template-image',
      },
      {
        title: 'markdown',
        $ref: '#/definitions/template-markdown',
      },
      {
        title: 'html',
        $ref: '#/definitions/template-html',
      },
    ],
  },
};
