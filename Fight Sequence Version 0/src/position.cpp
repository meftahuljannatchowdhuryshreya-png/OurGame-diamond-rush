 #include"position.h"
void LoadLevelPositions(int currentLevel,Enemy goblin[],int &goblinCount,Slime &slime,Spike &spike,LaserTrap level1Lasers[],LaserTrap level2Lasers[],LaserTrap level3Lasers[],LaserTrap level4Lasers[])
{
            if(currentLevel==0) {
                //level 1 lasers
               level1Lasers[0].start={306,452};
               level1Lasers[0].end={306,504};
               level1Lasers[1].start={331,240};
               level1Lasers[1].end={408,240};
               level1Lasers[2].start={611,368};
               level1Lasers[2].end={665,368};
               level1Lasers[3].start={755,264};
               level1Lasers[3].end={755,311};
               //goblin
                goblinCount=0;

            }else if(currentLevel==1) {
               //level 2 laser
               level2Lasers[0].start={400,172};
               level2Lasers[0].end={400,220};
               level2Lasers[1].start={592,172};
               level2Lasers[1].end={592,252};
               level2Lasers[2].start={400,300};
               level2Lasers[2].end={400,380};
               level2Lasers[3].start={400,490};
               level2Lasers[3].end={400,540};
               level2Lasers[4].start={592,388};
               level2Lasers[4].end={592,472};
               //goblin
                goblinCount=6;
               goblin[0].position = {64, 224};   // Left upper area
               goblin[1].position = {300, 224};  // left upper area
               goblin[1].moveRight=false;
               goblin[2].position = {680, 230};  // Upper right
               goblin[3].position = {64, 530};   // Lower left
               goblin[4].position = {200,360};  // Lower middle
               goblin[5].position = {970,230};  // upper right
               goblin[5].moveRight=false;

            }else if(currentLevel==2){
              //level 3 laser
            level3Lasers[0].start={326,208};
            level3Lasers[0].end={412,208};
            level3Lasers[1].start={432,106};
            level3Lasers[1].end={432,156};
            level3Lasers[2].start={708,238};
            level3Lasers[2].end={798,238};
            level3Lasers[3].start={900,432};
            level3Lasers[3].end={958,432};
            level3Lasers[4].start={134,400};
            level3Lasers[4].end={189,400};
               //goblin
                goblinCount=7;
            goblin[0].position = {300, 160};//top left
            goblin[1].position = {96, 352};//middle left
            goblin[2].position = {768, 352};//middle right
            goblin[2].moveRight = false;
            goblin[3].position = {410, 544};//bottom left
            goblin[4].position = {448, 544}; //bottom left
            goblin[5].position = {832, 544}; //bottom right
            goblin[5].moveRight = false;

            }else if(currentLevel==3) {
           //level 4 laser
            level4Lasers[0].start={528,388};
            level4Lasers[0].end={528,476};
            level4Lasers[1].start={656,108};
            level4Lasers[1].end={656,156};
            level4Lasers[2].start={656,300};
            level4Lasers[2].end={656,348};
            level4Lasers[3].start={656,452};
            level4Lasers[3].end={656,508};
                goblinCount=8;
            goblin[0].position = {96, 224};//upper left(2)
            goblin[0].moveRight = true;
            goblin[1].position = {464, 224};
            goblin[1].moveRight = false;

            goblin[2].position = {736, 128};//upper right(2)
            goblin[2].moveRight = true;
            goblin[3].position = {896, 128};
            goblin[3].moveRight = false;

            goblin[4].position = {848, 332};//middle right
            goblin[4].moveRight = false;
            goblin[5].position = {96, 514};//bottom left(2)
            goblin[5].moveRight = true;
            goblin[6].position = {130,514};

            goblin[7].position = {700, 516};//bottom right
            goblin[7].moveRight = true;
            }
    }