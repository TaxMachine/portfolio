import express from 'express';
import { rateLimit } from "express-rate-limit";
import { config } from "dotenv";
import cors from "cors";
import helmet from "helmet";

config();

const app = express();
app.disable("x-powered-by");
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cors());
app.use(helmet());
app.use(rateLimit({
    windowMs: 15 * 60 * 1000,
    limit: 100,
    message: "You have exceeded the 100 requests in 15 minutes limit!",
    standardHeaders: false,
    legacyHeaders: false,
}));