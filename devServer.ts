// import { Application, Router, send } from 'https://deno.land/x/oak@v6.5.0/mod.ts'
// import Plotly from 'https://cdn.skypack.dev/plotly.js?dts'
import { Webview } from 'https://deno.land/x/webview@0.6.0-pre.0/mod.ts'

// const app = new Application()
// const router = new Router()

// Plotly.newPlot('gd', [{y: [1, 2, 3]}])

const html = `<h1>Hello world</h1>`

const webview1 = new Webview({
    url: `data:text/html,${encodeURIComponent(html)}`
})

webview1.run()

// app.use(async (ctx, next) => {
//     await send(ctx, ctx.request.url.pathname, {
//         root: `${Deno.cwd()}/data/public`,
//     })
//     next()
// })

// app.use(router.routes())
// app.use(router.allowedMethods())

// router.get('/', ctx => {
//     const html = Deno.readTextFileSync(`${Deno.cwd()}/data/index.html`)
//     ctx.response.body = html
// })

// await app.listen({ port: 8080 })