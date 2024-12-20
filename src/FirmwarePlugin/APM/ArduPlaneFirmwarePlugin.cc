/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "ArduPlaneFirmwarePlugin.h"
#include "Vehicle.h"

bool ArduPlaneFirmwarePlugin::_remapParamNameIntialized = false;
FirmwarePlugin::remapParamNameMajorVersionMap_t ArduPlaneFirmwarePlugin::_remapParamName;

ArduPlaneFirmwarePlugin::ArduPlaneFirmwarePlugin(void)
    : _manualFlightMode      (tr("Manual"))
    , _circleFlightMode      (tr("Circle"))
    , _stabilizeFlightMode   (tr("Stabilize"))
    , _trainingFlightMode    (tr("Training"))
    , _acroFlightMode        (tr("Acro"))
    , _flyByWireAFlightMode  (tr("FBW A"))
    , _flyByWireBFlightMode  (tr("FBW B"))
    , _cruiseFlightMode      (tr("Cruise"))
    , _autoTuneFlightMode    (tr("Autotune"))
    , _autoFlightMode        (tr("Auto"))
    , _rtlFlightMode         (tr("RTL"))
    , _loiterFlightMode      (tr("Loiter"))
    , _takeoffFlightMode     (tr("Takeoff"))
    , _avoidADSBFlightMode   (tr("Avoid ADSB"))
    , _guidedFlightMode      (tr("Guided"))
    , _initializingFlightMode(tr("Initializing"))
    , _qStabilizeFlightMode  (tr("QuadPlane Stabilize"))
    , _qHoverFlightMode      (tr("QuadPlane Hover"))
    , _qLoiterFlightMode     (tr("QuadPlane Loiter"))
    , _qLandFlightMode       (tr("QuadPlane Land"))
    , _qRTLFlightMode        (tr("QuadPlane RTL"))
    , _qAutotuneFlightMode   (tr("QuadPlane AutoTune"))
    , _qAcroFlightMode       (tr("QuadPlane Acro"))
    , _thermalFlightMode     (tr("Thermal"))
{
    setModeEnumToModeStringMapping({
        {APMPlaneMode::MANUAL        , _manualFlightMode      },
        {APMPlaneMode::CIRCLE        , _circleFlightMode      },
        {APMPlaneMode::STABILIZE     , _stabilizeFlightMode   },
        {APMPlaneMode::TRAINING      , _trainingFlightMode    },
        {APMPlaneMode::ACRO          , _acroFlightMode        },
        {APMPlaneMode::FLY_BY_WIRE_A , _flyByWireAFlightMode  },
        {APMPlaneMode::FLY_BY_WIRE_B , _flyByWireBFlightMode  },
        {APMPlaneMode::CRUISE        , _cruiseFlightMode      },
        {APMPlaneMode::AUTOTUNE      , _autoTuneFlightMode    },
        {APMPlaneMode::AUTO          , _autoFlightMode        },
        {APMPlaneMode::RTL           , _rtlFlightMode         },
        {APMPlaneMode::LOITER        , _loiterFlightMode      },
        {APMPlaneMode::TAKEOFF       , _takeoffFlightMode     },
        {APMPlaneMode::AVOID_ADSB    , _avoidADSBFlightMode   },
        {APMPlaneMode::GUIDED        , _guidedFlightMode      },
        {APMPlaneMode::INITIALIZING  , _initializingFlightMode},
        {APMPlaneMode::QSTABILIZE    , _qStabilizeFlightMode  },
        {APMPlaneMode::QHOVER        , _qHoverFlightMode      },
        {APMPlaneMode::QLOITER       , _qLoiterFlightMode     },
        {APMPlaneMode::QLAND         , _qLandFlightMode       },
        {APMPlaneMode::QRTL          , _qRTLFlightMode        },
        {APMPlaneMode::QAUTOTUNE     , _qAutotuneFlightMode   },
        {APMPlaneMode::QACRO         , _qAcroFlightMode       },
        {APMPlaneMode::THERMAL       , _thermalFlightMode     },
    });

    if (!_remapParamNameIntialized) {
        FirmwarePlugin::remapParamNameMap_t& remapV3_10 = _remapParamName[3][10];

        remapV3_10["BATT_ARM_VOLT"] =    QStringLiteral("ARMING_VOLT_MIN");
        remapV3_10["BATT2_ARM_VOLT"] =   QStringLiteral("ARMING_VOLT2_MIN");

        _remapParamNameIntialized = true;
    }
}

int ArduPlaneFirmwarePlugin::remapParamNameHigestMinorVersionNumber(int majorVersionNumber) const
{
    // Remapping supports up to 3.10
    return majorVersionNumber == 3 ? 10 : Vehicle::versionNotSetValue;
}

uint32_t ArduPlaneFirmwarePlugin::_convertToCustomFlightModeEnum(uint32_t val) const
{
    switch (val) {
    case APMCustomMode::AUTO:
        return APMPlaneMode::AUTO;
    case APMCustomMode::GUIDED:
        return APMPlaneMode::GUIDED;
    case APMCustomMode::RTL:
        return APMPlaneMode::RTL;
    case APMCustomMode::SMART_RTL:
        return APMPlaneMode::RTL;
    }
    return UINT32_MAX;
}
