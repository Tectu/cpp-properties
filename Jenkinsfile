pipeline {
    agent any

    stages {
        stage('Run cmake')
        {
            parallel
            {
                stage('Windows')
                {
                    agent { label 'Windows' }
                    steps
                    {
                        dir('Run CMake') {
                            sh "rm -rf *"
                            sh "cmake -G'MSYS Makefiles' .."
                        }
                    }
                }

                stage('Unix')
                {
                    agent { label 'FreeBSD' }
                    steps
                    {
                        dir('Run CMake') {
                            sh "rm -rf *"
                            sh "cmake -G'Unix Makefiles' .."
                        }
                    }
                }
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
                sh "cppcheck -j 4 --enable=all --inconclusive --xml --xml-version=2 lib -ilib/3rdparty 2> cppcheck.xml"
                publishCppcheck(
                    pattern: '**/cppcheck.xml'
                )
            }
        }
    }
}
