pipeline {
    agent { label 'FreeBSD' }

    stages {
        stage('Run cmake')
        {
            parallel
            {
                stage('Windows')
                {
                    agent { label 'Windows' }
                    stages
                    {
                        stage('CMake [Windows]')
                        {
                            steps
                            {
                                dir('build') {
                                    sh "rm -rf *"
                                    sh "cmake -G'MSYS Makefiles' .."
                                }
                            }
                        }

                        stage('Build [Windows]')
                        {
                            steps
                            {
                                dir('build') {
                                    sh 'make -j8'
                                }
                            }
                        }
                    }
                }

                stage('Unix')
                {
                    agent { label 'FreeBSD' }
                    stages
                    {
                        stage('CMake [FreeBSD]')
                        {
                            steps
                            {
                                dir('build') {
                                    sh "rm -rf *"
                                    sh "cmake -G'Unix Makefiles' .."
                                }
                            }
                        }

                        stage('Build [FreeBSD]')
                        {
                            steps
                            {
                                dir('build') {
                                    sh 'make -j8'
                                }
                            }
                        }

                        stage('Test [FreeBSD]')
                        {
                            steps
                            {
                                dir('build/test') {
                                    sh "./tests"
                                }
                            }
                        }

                        stage('Analysis [FreeBSD]')
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
            }
        }
    }
}
