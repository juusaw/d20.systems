# d20.systems

A client for [d20ql](https://github.com/juusaw/d20ql/) API.

## Development

```sh
npm install
npm start
npm server # in another tab
```

Navigate to [localhost:8000](http://localhost:8000).


## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version as well as copy `src/index.html` into `build/`. You can then deploy the contents of the `build` directory (`index.html` and `Index.js`).

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
