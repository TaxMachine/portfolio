import express from 'express';
import { rateLimit } from "express-rate-limit";
import { config } from "dotenv";
import cors from "cors";
import helmet from "helmet";
import { join } from "path";

config();

const app = express();
app.disable("x-powered-by");
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(join(__dirname, "public")));
app.use(cors());
app.use(helmet({
    contentSecurityPolicy: {
        directives: {
            "img-src": ["'self'", "https://*.github.com/*", "https://*.githubusercontent.com/*", "https://github-readme-stats.vercel.app/*"],
            "script-src": ["'self'", "https://code.jquery.com/*", "https://cdn.jsdelivr.net/*"],
            "style-src": ["'self'", "https://cdn.jsdelivr.net/*", "https://fonts.googleapis.com/*"],
        }
    }
}));
app.use(rateLimit({
    windowMs: 15 * 60 * 1000,
    limit: 100,
    message: "You have exceeded the 100 requests in 15 minutes limit!",
    standardHeaders: false,
    legacyHeaders: false,
}));

app.set('view engine', 'pug');

import { routers } from './routers/routers';

app.use('/', routers);

app.listen(process.env.PORT, () => {
    console.log(`Server is running on http://localhost:${process.env.PORT}`);
});