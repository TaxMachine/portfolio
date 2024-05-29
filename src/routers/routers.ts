import { Router } from 'express';

const router = Router();

import { homeRouter } from './web/home';

router.use('/', homeRouter);

export { router as routers };