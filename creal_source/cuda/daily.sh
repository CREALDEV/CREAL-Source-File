#!/bin/bash

#upload the current creal build to alpha
mv crealDaily.tar crealDaily.tar_old
tar -cvvf crealDaily.tar creal_work_folder_v4/

#now uploading to alpha

scp crealDaily.tar romxero@alpha:~/crealDaily.tar


