"""
main script for doing tpc calibration with dnn
"""

import yaml
from machine_learning_hep.logger import get_logger
#from machine_learning_hep.utilities import checkdir, checkmakedir
from dnnoptimiser import DnnOptimiser

## optionally limit GPU memory usage
# import tensorflow as tf
# gpus = tf.config.experimental.list_physical_devices('GPU')
# if gpus:
#   try:
#     for gpu in gpus:
#       tf.config.experimental.set_memory_growth(gpu, True)
#   except RuntimeError as e:
#     print(e)

def do_entire_analysis():

    logger = get_logger()
    logger.info("Do analysis chain")

    with open("default.yaml", 'r') as default_data:
        default = yaml.safe_load(default_data)
    case = default["case"]
    df_parameters = "database_parameters_%s.yml" % case
    with open(df_parameters, 'r') as parameters_data:
        db_parameters = yaml.safe_load(parameters_data)


    #dirmodel = db_parameters[case]["dirmodel"]
    #dirval = db_parameters[case]["dirval"]
    #dirinput = db_parameters[case]["dirinput"]

    dodumpflattree = default["dumpflattree"]
    dotrain = default["dotrain"]
    doapply = default["doapply"]
    doplot = default["doplot"]
    doNDvalidation = default["doNDvalidation"]
    doCreateNDHistogramsFromTree = default["doCreateNDHistogramsFromTree"]
    doCreatePDFMaps = default["doCreatePDFMaps"]
    dogrid = default["dogrid"]

    #counter = 0
    #if dotraining is True:
    #    counter = counter + checkdir(dirmodel)
    #if dotesting is True:
    #    counter = counter + checkdir(dirval)
    #if counter < 0:
    #    sys.exit()

    myopt = DnnOptimiser(db_parameters[case], case)

    #if dotraining is True:
    #    checkmakedir(dirmodel)
    #if dotesting is True:
    #    checkmakedir(dirval)

    if dodumpflattree is True:
        myopt.dumpflattree()
    if dotrain is True:
        myopt.train()
    if doapply is True:
        myopt.apply()
    if doplot is True:
        myopt.plot()
    if doNDvalidation is True:
        myopt.createNDvalidationData()
    if doCreateNDHistogramsFromTree is True:
        myopt.createNDHistosFromTree()
    if doCreatePDFMaps is True:
        myopt.createPDFMaps()
    if dogrid is True:
        myopt.gridsearch()

do_entire_analysis()
