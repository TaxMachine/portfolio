import express, { Router, Request, Response } from 'express';
import { join } from 'path';

const router = Router();

router.get('/', async (req: Request, res: Response) => {
    res.render(join(__dirname, 'views', 'home.pug'), {
        title: 'Home',
    });
});

export { router as homeRouter };