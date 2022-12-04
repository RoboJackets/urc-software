const util = require('util');
const exec = util.promisify(require('child_process').exec);
const path = require('path');
const commandLineArgs = require('command-line-args');
const { string } = require('yargs');


/* first - parse the main command */
const mainDefinitions = [
  { name: 'command', defaultOption: true }
];
const mainOptions = commandLineArgs(mainDefinitions, { stopAtFirstUnknown: true });
const argv = mainOptions._unknown || [];

/* second - parse the merge command options */
let optimizeOptions = {};
if (mainOptions.command === 'auto') {
  const mergeDefinitions = [
    { name: 'backupFiles', type: Boolean, defaultValue: true },
    { name: 'usingWebViewerServer', type: Boolean, defaultValue: false },
    { name: 'willConvertToXod', type: Boolean, defaultValue: false },
    { name: 'needClientSideOfficeSupport', type: Boolean, defaultValue: true },
    { name: 'useLegacyOffice', type: Boolean, defaultValue: false },
    { name: 'useLeanPDF', type: Boolean, defaultValue: false },
    { name: 'useContentEdit', type: Boolean, defaultValue: false },
    { name: 'salesforceSupport', type: Boolean, defaultValue: false },
    { name: 'deleteUnused', type: Boolean, defaultValue: true },
    { name: 'useSourceMap', type: Boolean, defaultValue: false },
    { name: 'excludeOptimizedWorkers', type: Boolean, defaultValue: false },
  ];
  optimizeOptions = commandLineArgs(mergeDefinitions, { argv });
}

//============== Command Arg End ============

const GREEN = '\x1b[32m';
const CYAN = '\x1b[36m';
const MAGENTA = '\x1b[35m';
const RESET = '\x1b[0m';
const DIM = '\x1b[2m';
const RED = '\x1b[31m';
const BLINK = '\x1b[5m';
const UNDER = '\x1b[4m';

const resourceDir = path.resolve(__dirname, '../webviewer-salesforce/');
const resourcesForZip = [
  [`${resourceDir}/resource`],
  [`${resourceDir}/external`],
];
const globalPrompt = {
  message: "Answer must be 'y' or 'n'",
  pattern: /^[yn]$/,
  required: true,
  type: 'string',
};


(async () => {
  try {
    require.resolve('prompt');
    require.resolve('fs-extra');
    require.resolve('archiver');
  } catch (e) {
    console.log(CYAN, 'Installing required dependencies...', RESET);
    await exec('npm i prompt --save-dev && npm i fs-extra --save-dev && npm i archiver --save-dev');
  }

  const prompt = require('prompt');
  const fs = require('fs-extra');
  const archiver = require('archiver');

  let wvFolder = 'lib' ;
  let isNPMPackage = false;
  const packageJsonExists = await fs.pathExists(path.resolve(__dirname, '../package.json'));
  if (packageJsonExists) {
    // if this is npm package use "public" instead of "lib"
    const rawdata = fs.readFileSync(path.resolve(__dirname, '../package.json'));
    const packageJson = JSON.parse(rawdata);
    if (packageJson.name === '@pdftron/webviewer') {
      wvFolder = 'public';
      isNPMPackage = true;
    }
  }

  console.log(CYAN, `\nThis script will delete any files you won\'t be using in your ${wvFolder} folder. Please use with caution!`);
  console.log(CYAN, `\nPress CTRL + C at any time to safely cancel this process. If you are unsure of any answer, ${UNDER}please clarify${RESET}${CYAN} before answering them.`, RESET);

  prompt.start();
  prompt.message = `${MAGENTA}\nOptimize`;
  prompt.delimiter = `: ${RESET}`;

  const backupExists = await fs.pathExists(path.resolve(__dirname, `../${wvFolder}-backup`));
  if (backupExists) {
    console.log(CYAN, '\nA backup will not be created because a backup already exists!');
  }

  const schema = {
    properties: {
      backup: {
        description: `Do you want us to backup your files before optimizing? [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => {
          if (optimizeOptions.hasOwnProperty('backupFiles')) {
            return false;
          }
          return !backupExists;
        },
      },
      excludeOptimizedWorkers: {
        description: `Do you want to exclude the use of optimized worker files? If you exclude them make sure that you pass 'enableOptimizedWorkers: false' to the WebViewer constructor. [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => {
          return !optimizeOptions.hasOwnProperty('excludeOptimizedWorkers');
        },
      },
      webViewerServer: {
        description: `Will you be using WebViewer Server? See ${CYAN}https://www.pdftron.com/documentation/web/guides/wv-server/${RESET}${DIM} for more info. [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => {
          return !optimizeOptions.hasOwnProperty('usingWebViewerServer');
        },
      },
      xod: {
        description: `Will you be converting all your documents to XOD? See ${CYAN}https://www.pdftron.com/documentation/web/guides/optimize-lib-folder${RESET}${DIM} for more info. [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => {
          if (optimizeOptions.hasOwnProperty('willConvertToXod')) {
            return false;
          }
          return prompt.history('webViewerServer').value === 'n';
        },
      },
      office: {
        description: `Do you need client side office support (docx, pptx, xlsx)? [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => {
          if (optimizeOptions.hasOwnProperty('needClientSideOfficeSupport')) {
            return false;
          }
          return prompt.history('xod') && prompt.history('xod').value === 'n' && prompt.history('webViewerServer').value === 'n';
        },
      },
      useLegacyOffice: {
        description: `Do you need client side office support for legacy office files (doc, ppt, xls)? [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => prompt.history('office') && prompt.history('office').value === 'y',
      },
      useLeanPDF: {
        description: `Do you need the full PDF API? See ${CYAN}https://www.pdftron.com/documentation/web/guides/optimize-lib-folder${RESET}${DIM} for more info (most users dont need this option). [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => prompt.history('xod') && prompt.history('xod').value === 'n' && prompt.history('webViewerServer').value === 'n',
      },
      pdfnetProd: {
        description: `Do you want to use the production version of PDFNet.js? The production version does not have type checking and console messages, but is much smaller than the development version. [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => prompt.history('useLeanPDF') && prompt.history('useLeanPDF').value === 'y',
      },
      useContentEdit: {
        description: `Do you need to use the content editing feature? (This is for editing content on the page in the viewer) [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => prompt.history('xod') && prompt.history('xod').value === 'n' && prompt.history('webViewerServer').value === 'n',
      },
      salesforceSupport: {
        description: `Do you need to deploy to Salesforce? See ${CYAN}https://www.pdftron.com/documentation/web/guides/optimize-lib-folder${RESET}${DIM} for more info (most users dont need this option). [y/n]${RESET}`,
        ...globalPrompt,
        ask: () => prompt.history('xod') && prompt.history('xod').value === 'n' && prompt.history('webViewerServer').value === 'n',
      },
      useSourceMap: {
        description: `Do you need the source map for WebViewer's UI? The source map allows you to debug WebViewer's UI on your site using unminified code. [y/n]${RESET}`,
        ...globalPrompt,
      },
    },
  };

  prompt.get(schema, (err, result) => {
    if (err) {
      console.log(`\n\n${RED}Process exited. No action will be taken.${RESET}\n`);
      return;
    }

    let {
      excludeOptimizedWorkers = 'n',
      xod = 'n',
      office = 'n',
      useLegacyOffice = 'n',
      useLeanPDF = 'n',
      pdfnetProd = 'n',
      backup = 'n',
      salesforceSupport = 'n',
      webViewerServer = 'n',
      useContentEdit = 'n',
      useSourceMap = 'n',
    } = result;

    if (mainOptions.command === 'auto') {
      backup = optimizeOptions.backupFiles ? 'y' : 'n';
      excludeOptimizedWorkers = optimizeOptions.excludeOptimizedWorkers ? 'y' : 'n';
      webViewerServer = optimizeOptions.usingWebViewerServer ? 'y' : 'n';
      xod = optimizeOptions.willConvertToXod ? 'y' : 'n';
      office = optimizeOptions.needClientSideOfficeSupport ? 'y' : 'n';
      useLegacyOffice = optimizeOptions.useLegacyOffice ? 'y' : 'n';
      useLeanPDF = optimizeOptions.useLeanPDF ? 'y' : 'n';
      salesforceSupport = optimizeOptions.salesforceSupport ? 'y' : 'n';
      useContentEdit = optimizeOptions.useContentEdit ? 'y' : 'n';
      useSourceMap = optimizeOptions.useSourceMap ? 'y' : 'n';
    }

    const filesToDelete = [];
    const filesToDeleteForSalesforce = [];

    const filesToRelocate = [
      [path.resolve(__dirname, `../${wvFolder}/core/pdf/pdfnet.res`), `${resourceDir}/resource`],
      [path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFworker.js`), `${resourceDir}/resource`],
      [path.resolve(__dirname, `../${wvFolder}/core/external/`), `${resourceDir}/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/assets`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/external`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.js`), `${resourceDir}/${wvFolder}/core/pdf/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/webviewer-core.min.js`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/CORSWorker.js`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/DecryptWorker.js`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/core/Worker.js`), `${resourceDir}/${wvFolder}/core/`, true],
      [path.resolve(__dirname, `../${wvFolder}/ui`), `${resourceDir}/${wvFolder}/`, true],
    ];

    // in npm page these files does not exist
    if (!isNPMPackage) {
      filesToRelocate.push([path.resolve(__dirname, `../${wvFolder}/package.json`), `${resourceDir}/${wvFolder}/`, true]);
      filesToRelocate.push([path.resolve(__dirname, `../${wvFolder}/webviewer.min.js`), `${resourceDir}/${wvFolder}/`, true]);
    }

    // Add chunk files to filesToRelocate
    let files = fs.readdirSync(path.resolve(__dirname, `../${wvFolder}/core`));
    files = files.filter((file) => file.indexOf('.chunk.') > -1);
    files.forEach((file) => {
      filesToRelocate.push([path.resolve(__dirname, `../${wvFolder}/core/${file}`), `${resourceDir}/${wvFolder}/core/`, true]);
    });

    if (excludeOptimizedWorkers === 'y') {
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/optimized`),
      );
    }

    // If they are not using XOD
    if (webViewerServer === 'n' && xod === 'n') {
      // if they dont need office
      if (office === 'n') {
        filesToDelete.push(
          path.resolve(__dirname, `../${wvFolder}/core/office`),
          path.resolve(__dirname, `../${wvFolder}/core/legacyOffice`),
        );
      } else {
        filesToRelocate.push(
          [path.resolve(__dirname, `../${wvFolder}/core/office/OfficeWorker.js`), `${resourceDir}/office`],
          [path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorkerWasm.br.wasm`), `${resourceDir}/office`],
          [path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorkerWasm.br.js.mem`), `${resourceDir}/office`],
          [path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorker.br.js.mem`), `${resourceDir}/office_asm`],
          [path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorker.br.mem`), `${resourceDir}/office_resource`],
        );
        resourcesForZip.push(
          [`${resourceDir}/office`],
          [`${resourceDir}/office_asm`],
          [`${resourceDir}/office_resource`],
        );

        if (useLegacyOffice === 'n') {
          filesToDelete.push(
            path.resolve(__dirname, `../${wvFolder}/core/legacyOffice`),
          );
        } else {
          filesToRelocate.push(
            [path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/LegacyOfficeWorker.js`), `${resourceDir}/legacyOffice`],
            [path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/WebB2XOfficeWorkerWasm.br.wasm`), `${resourceDir}/legacyOffice`],
            [path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/WebB2XOfficeWorkerWasm.br.js.mem`), `${resourceDir}/legacyOffice`],
            [path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/WebB2XOfficeWorker.br.js.mem`), `${resourceDir}/legacyOffice_asm`],
            [path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/WebB2XOfficeWorker.br.mem`), `${resourceDir}/legacyOffice_resource`],
          );
          resourcesForZip.push(
            [`${resourceDir}/legacyOffice`],
            [`${resourceDir}/legacyOffice_asm`],
            [`${resourceDir}/legacyOffice_resource`],
          );
        }
      }

      // If they dont need the full api
      if (useLeanPDF === 'n') {
        filesToDelete.push(
          path.resolve(__dirname, `../${wvFolder}/core/pdf/full`),
        );
        filesToRelocate.push(
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFNetCWasm.br.js.mem`), `${resourceDir}/pdf_lean/lean`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFNetCWasm.br.wasm`), `${resourceDir}/pdf_lean/lean`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFNetC.br.js.mem`), `${resourceDir}/asm_lean/lean`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFNetC.gz.mem`), `${resourceDir}/resource/lean`],
        );
        resourcesForZip.push(
          [`${resourceDir}/pdf_lean`],
          [`${resourceDir}/asm_lean`],
        );
      }
      // If they do need the full API
      else {
        filesToDelete.push(
          path.resolve(__dirname, `../${wvFolder}/core/pdf/lean`),
        );

        if (pdfnetProd === 'y') {
          // replace PDFNet.js with PDFNet.prod.js
          fs.removeSync(path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.js`));
          fs.renameSync(
            path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.prod.js`),
            path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.js`),
          );
        } else {
          fs.removeSync(path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.prod.js`));
        }

        filesToRelocate.push(
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFNetCWasm.br.js.mem`), `${resourceDir}/pdf_full/full`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFNetCWasm.br.wasm`), `${resourceDir}/pdf_full/full`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFNetC.br.js.mem`), `${resourceDir}/asm_full/full`],
          [path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFNetC.gz.mem`), `${resourceDir}/resource/full`],
        );
        resourcesForZip.push(
          [`${resourceDir}/pdf_full`],
          [`${resourceDir}/asm_full`],
        );
      }
    }
    // if they are using XOD
    else if (webViewerServer === 'n') {
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/core/office`),
        path.resolve(__dirname, `../${wvFolder}/core/legacyOffice`),
      );
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/core/pdf`),
      );
    }

    if (webViewerServer === 'y') {
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/core/pdf/PDFNet.js`),
        path.resolve(__dirname, `../${wvFolder}/core/office`),
        path.resolve(__dirname, `../${wvFolder}/core/legacyOffice`),
        path.resolve(__dirname, `../${wvFolder}/core/pdf/full`),
      );
    }

    if (useContentEdit === 'n') {
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/core/contentEdit`),
      );
    } else {
      filesToRelocate.push(
        [path.resolve(__dirname, `../${wvFolder}/core/contentEdit/InfixServerWasm.br.js.mem`), `${resourceDir}/content_edit`],
        [path.resolve(__dirname, `../${wvFolder}/core/contentEdit/InfixServerWasm.br.wasm`), `${resourceDir}/content_edit`],
        [path.resolve(__dirname, `../${wvFolder}/core/contentEdit/InfixServerWasm.gz.js.mem`), `${resourceDir}/content_edit`],
        [path.resolve(__dirname, `../${wvFolder}/core/contentEdit/InfixServerModule.js`), `${resourceDir}/content_edit`],
        [path.resolve(__dirname, `../${wvFolder}/core/contentEdit/InfixServerWasm.br.mem`), `${resourceDir}/content_edit_resource`],
      );
      resourcesForZip.push(
        [`${resourceDir}/content_edit`],
        [`${resourceDir}/content_edit_resource`],
      );
    }

    if (salesforceSupport === 'y') {
      // If they dont need the full api
      if (useLeanPDF === 'n') {
        filesToDeleteForSalesforce.push(
          path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFWorker.nmf`),
          path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFWorker.pexe`),
          path.resolve(__dirname, `../${wvFolder}/core/pdf/lean/PDFWorkerSubzero.nmf`),
        );
      }
      // If they do need the full API
      else {
        filesToDeleteForSalesforce.push(
          path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFWorker.nmf`),
          path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFWorker.pexe`),
          path.resolve(__dirname, `../${wvFolder}/core/pdf/full/PDFWorkerSubzero.nmf`),
        );
      }

      filesToDeleteForSalesforce.push(
        path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorker.nmf`),
        path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorker.pexe`),
        path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorkerSubzero.nmf`),
        path.resolve(__dirname, `../${wvFolder}/core/office/WebOfficeWorkerWasm.br.wasm`),
        path.resolve(__dirname, `../${wvFolder}/core/legacyOffice/WebB2XOfficeWorkerWasm.br.wasm`),
      );
      resourcesForZip.push([`${resourceDir}/${wvFolder}`]);
    }

    if (useSourceMap === 'n') {
      filesToDelete.push(
        path.resolve(__dirname, `../${wvFolder}/ui/webviewer-ui.min.js.map`),
        path.resolve(__dirname, `../${wvFolder}/ui/style.css.map`)
      );
    }

    console.log(`\n==== ${RED}${BLINK + UNDER}FILES & FOLDERS TO DELETE${RESET} ====\n`);

    filesToDelete.forEach((f) => {
      console.log(`${RED}${f}${RESET}`);
    });

    console.log('\n===================================');

    prompt.get({
      properties: {
        delete: {
          description: `The above files will be permanently deleted. Is this okay? ${backup === 'y' ? `(A backup will be created in './${wvFolder}-backup')` : '(A backup will NOT be created)'} [y|n]${RESET}`,
          ...globalPrompt,
          ask: () => {
            if (mainOptions.command === 'auto') {
              return false;
            }
            return true;
          }
        },
      },
    }, async (err, result) => {
      if (err) {
        console.log(`\n\n${RED}Process exited. No action will be taken.${RESET}\n`);
        return;
      }
      if (mainOptions.command === 'auto') {
        result.delete = optimizeOptions.deleteUnused;
      }
      if (result.delete === 'y') {
        if (backup === 'y') {
          console.log(`\n${GREEN}Creating backup...${RESET}`);
          await fs.copy(
            path.resolve(__dirname, `../${wvFolder}`),
            path.resolve(__dirname, `../${wvFolder}-backup`),
          );
        }

        console.log(`\n${GREEN}Deleting files...${RESET}`);

        const promises = filesToDelete.map((file) => fs.remove(file));

        await Promise.all(promises);

        if (salesforceSupport === 'y') {
          console.log(`\n${GREEN}Extracting files for salesforce build...${RESET}`);
          const relocatePromises = filesToRelocate.map(([file, dest, isCopy]) => {
            const f = path.basename(file);
            dest = path.resolve(dest, f);
            const func = (isCopy) ? fs.copy : fs.copy;
            return func(file, dest);
          });

          try {
            await Promise.all(relocatePromises);
          } catch (error) {
            console.log(error);
          }

          console.log(`\n${GREEN}Compressing files...${RESET}`);

          const sfXmlContent = `<?xml version="1.0" encoding="UTF-8"?>
          <StaticResource xmlns="http://soap.sforce.com/2006/04/metadata">
              <cacheControl>Public</cacheControl>
              <contentType>application/zip</contentType>
          </StaticResource>`;

          const zipPromises = resourcesForZip.map((item) => {
            const [source, tmp = ''] = item;
            return new Promise(function(resolve, reject) {
              const output = fs.createWriteStream(`${source}.zip`);
              try {
                fs.appendFileSync(`${source}.resource-meta.xml`, sfXmlContent);
              } catch (err) {
                throw err;
              }
              const archive = archiver('zip', {
                zlib: {
                  level: 9,
                }, // Sets the compression level.
              });
              output.on('close', () => {
                const fi = path.basename(source);
                console.log(`${fi}.zip`);
                // fs.remove(source);
                resolve();
              });
              archive.on('error', reject);
              archive.pipe(output);
              archive.directory(source, tmp);
              archive.finalize();
            });
          });
          await Promise.all(zipPromises);
          console.log(`\n${GREEN}${UNDER}Done! Copy above zipped files and all ".resource-meta.xml" files into "staticresources" folder of your salesforce app.${RESET}\n`);
          return;
        }
      } else {
        console.log(`\n${RED}Process exited. No action will be taken.${RESET}\n`);
        return;
      }

      console.log(`\n${GREEN}${UNDER}Done! Your ${wvFolder} folder is now optimized for production use.${RESET}\n\n`);
    });
  });
})();