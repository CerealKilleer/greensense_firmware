/*
 * Copyright (C) 2025 Yonathan López Mejía, Juana María Rodas Álvarez, Juan Esteban López Domínguez
 *
 * Este archivo forma parte de GreenSense.
 *
 * GreenSense se distribuye con la esperanza de que sea útil,
 * pero SIN NINGUNA GARANTÍA; sin incluso la garantía implícita de
 * COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Para más detalles,
 * consulte la Licencia Pública General de GNU, versión 3.
 *
 * Usted debe haber recibido una copia de la Licencia Pública General de GNU
 * junto con GreenSense. Si no es así, consulte
 * <http://www.gnu.org/licenses/>.
 */

#include <Arduino.h>
#include "app.hpp"

void setup()
{
  app_init();
}

void loop()
{
  app_main();
}