pipeline {
    agent any

    stages {
        stage('Run cmake')
        {
            steps
            {
                cmakeBuild(
                    buildDir: 'build',
                    cleanBuild: true,
                    generator: 'Unix Makefiles',
                    installation: 'InSearchPath'
                )
            }
        }

        stage('Build')
        {
            steps
            {
                dir('build') {
                    sh 'make -j4'
                }
            }
        }

        stage('Test')
        {
            steps
            {
                dir('build/test') {
                    sh "./tests"
                }
            }
        }

        stage('Analysis')
        {
            steps
            {
                sh "cppcheck -j 4 --enable=all --inconclusive --xml --xml-version=2 . -ibuild -ilib/3rdparty 2> cppcheck.xml"
                publishCppcheck(
                    pattern: '**/cppcheck.xml'
                )
            }
        }
    }
}

